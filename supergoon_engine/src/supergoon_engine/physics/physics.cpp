#include <supergoon_engine/physics/physics.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/objects/actor.hpp>
#include <supergoon_engine/objects/tile.hpp>

using namespace Physics;
using namespace Components;
using namespace Objects;

void Physics::ApplyPhysics(const Gametime &gametime, Components::RigidbodyComponent &rigidbody, std::vector<Tile *> tiles, std::vector<Objects::Actor *> actors, Gravity::GravityParams params)
{

    rigidbody.ApplyAcceleration();

    if (rigidbody.gravity_enabled)
        Gravity::ApplyGravity(rigidbody, params, gametime);

    if (rigidbody.velocity == Vector2::Zero())
        return;

    auto physics_params = PhysicsParams(gametime, rigidbody, tiles, actors, params);

    ApplyVelocityX(physics_params);
    ApplyVelocityY(physics_params);
}

void Physics::ApplyVelocityX(PhysicsParams& params)
{
    auto x_step = params.rigidbody->velocity.x * params.gametime->ElapsedTimeInSeconds();
    auto minimum_step = params.rigidbody->minimum_x_step;
    auto &loc_to_alter = params.rigidbody->owner_->location.x;
    auto &velocity_to_alter = params.rigidbody->velocity.x;
    Components::OverlapDirection overlap_dir = (x_step > 0) ? Components::OverlapDirection::Right : Components::OverlapDirection::Left;
    auto step_params = StepParams(x_step, minimum_step, loc_to_alter, velocity_to_alter, overlap_dir, true);
    TryAllMovementSteps(params, step_params);
}
void Physics::ApplyVelocityY(PhysicsParams& params)
{
    auto y_step = params.rigidbody->velocity.y * params.gametime->ElapsedTimeInSeconds();
    auto minimum_step = params.rigidbody->minimum_y_step;
    auto &loc_to_alter = params.rigidbody->owner_->location.y;
    auto &velocity_to_alter = params.rigidbody->velocity.y;
    Components::OverlapDirection overlap_dir = (y_step > 0) ? Components::OverlapDirection::Down : Components::OverlapDirection::Up;
    auto step_params = StepParams(y_step, minimum_step, loc_to_alter, velocity_to_alter, overlap_dir, false);
    TryAllMovementSteps(params, step_params);
}

void Physics::TryAllMovementSteps(PhysicsParams& physics_params, StepParams& step_params)
{
    auto steps_left = step_params.full_step;
    auto step_speed = (steps_left > 0) ? 1 : -1;
    bool collision = false;

    while ((steps_left >= step_params.minimum_step || steps_left <= -step_params.minimum_step) && !collision)
    {
        double move_step = 0;
        // Step one at a time, unless we are less than 1 in either direction.
        if (steps_left > 0)
            move_step = (steps_left >= step_speed) ? step_speed : steps_left;
        else
            move_step = (steps_left <= step_speed) ? step_speed : steps_left;
        auto box_location = physics_params.rigidbody->box_collider->GetCurrentSdlRectF();

        auto box_loc_to_change = (step_params.x_step) ? &box_location.x : &box_location.y;
        *box_loc_to_change += move_step;
        step_params.frect = &box_location;

        collision = TryMovementStep(physics_params, step_params);
        if (collision)
        {
            if(step_params.x_step == false)
            {
                std::cout << "Here";

            }
            *step_params.vel_to_alter = 0;
            if (!step_params.x_step && step_speed > 0)
            {
                physics_params.rigidbody->on_ground = true;
            }
            if (step_params.x_step)
            {
                physics_params.rigidbody->is_moving_x = false;
            }
            break;
        }
        *step_params.loc_to_alter += move_step;
        steps_left -= move_step;
    }
    // Returns if we are on the ground, useful for y conversions as this will set that variable.
    // If it is not x direction, and there is a collision, and we are moving downward.
    // TODO do this differently.

    // if (physics_params.rigidbody->on_ground && !collision && !step_params.x_step)
    // {
    //     SDL_FRect float_rect;
    //     auto box_location = physics_params.rigidbody->box_collider->GetCurrentSdlRectF();
    //     auto box_loc_to_change = (step_params.x_step) ? &box_location.x : &box_location.y;
    //     step_params.frect = &box_location;
    //     step_params.loc_to_alter = box_loc_to_change;
    //     *box_loc_to_change += 0.1f;
    //     collision = TryMovementStep(physics_params, step_params);
    //     if (!collision)
    //     {
    //         physics_params.rigidbody->on_ground = false;
    //     }
    // }
}

bool Physics::TryMovementStep(PhysicsParams& physics_params, StepParams& step_params)
{
    auto tiles = physics_params.tiles;
    auto rect = step_params.frect;
    auto actors = physics_params.actors;
    auto rigidbody = *physics_params.rigidbody;
    auto overlap_dir = step_params.overlap_dir;
    for (auto tile : tiles)
    {
        auto float_rect = tile->box_collider_component->GetCurrentSdlRectF();

        if (SDL_HasIntersectionF(rect, &float_rect))
        {
            return true;
        }
    }

    for (auto actor : actors)
    {
        if (actor->id == rigidbody.owner_->id)
            continue;
        auto actor_rects = actor->GetBoxColliders();

        for (auto &&actor_rect : actor_rects)
        {
            auto sdl_actor_rect = actor_rect->rectangle.sdl_rectangle;

            if (SDL_HasIntersectionF(rect, &sdl_actor_rect))
            {
                if (actor_rect->is_blocking)
                    return true;
                rigidbody.box_collider->AddToOverlaps(actor_rect);
                auto overlap_just_began = rigidbody.CheckIfOverlapJustBegan(actor_rect->id);
                if (overlap_just_began)
                {
                    auto args = Components::BoxColliderEventArgs(rigidbody.owner_, overlap_dir);
                    actor_rect->OnOverlapBeginEvent(args);
                }
            }
        }
    }
    return false;
}