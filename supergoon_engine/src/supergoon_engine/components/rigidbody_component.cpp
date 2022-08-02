#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/engine/gravity.hpp>
#include <supergoon_engine/engine/level.hpp>
#include <algorithm>

Components::RigidbodyComponent::RigidbodyComponent(GameObject *owner, Point box_size, Vector2 offset) : Component{owner, offset, 3}
{
    box_collider = new BoxColliderComponent(owner, box_size, offset);
}

Components::RigidbodyComponent::~RigidbodyComponent()
{
}
void Components::RigidbodyComponent::Update(const Gametime &gametime)
{

    accel_applied_this_frame = false;
    if (acceleration != Vector2::Zero())
    {
        velocity += acceleration;
        acceleration = Vector2::Zero();
        accel_applied_this_frame = true;
    }
    if (gravity_enabled)
        Gravity::ApplyGravity(*this, owner_->GetLevel()->gravity_params, gametime);

    if (velocity != Vector2::Zero())
        ApplyVelocity(gametime);

    // Check against actors avter moving
    auto box_location = box_collider->GetCurrentSdlRect();
    SDL_FRect float_rect;
    float_rect.x = box_location.x;
    float_rect.y = box_location.y;
    float_rect.w = box_location.w;
    float_rect.h = box_location.h;
    TryActorStep(float_rect);
}

void Components::RigidbodyComponent::ApplyVelocity(const Gametime &gametime)
{

    velocity.x = (velocity.x > 0) ? std::clamp(velocity.x, 0.f, max_velocity.x) : std::clamp(velocity.x, -max_velocity.x, 0.f);
    velocity.y = (velocity.y >= 0) ? std::clamp(velocity.y, 0.f, max_velocity.y) : std::clamp(velocity.y, -max_velocity.y, 0.f);

    auto x_step = velocity.x * gametime.ElapsedTimeInSeconds();
    auto y_step = velocity.y * gametime.ElapsedTimeInSeconds();
    ApplyVelocityByStepSolidsX(x_step);
    ApplyVelocityByStepSolidsY(y_step);
}
void Components::RigidbodyComponent::ApplyVelocityByStepSolidsX(double step)
{
    auto minimum_step = minimum_x_step;
    auto &loc_to_alter = owner_->location.x;
    auto &velocity_to_alter = velocity.x;
    Components::OverlapDirection overlap_dir = (step > 0) ? Components::OverlapDirection::Right : Components::OverlapDirection::Left;
    TryAllMovementSteps(step, minimum_step, loc_to_alter, velocity_to_alter, true, overlap_dir);
}
void Components::RigidbodyComponent::ApplyVelocityByStepSolidsY(double step)
{
    auto minimum_step = minimum_y_step;
    auto &loc_to_alter = owner_->location.y;
    auto &velocity_to_alter = velocity.y;
    Components::OverlapDirection overlap_dir = (step > 0) ? Components::OverlapDirection::Down : Components::OverlapDirection::Up;
    TryAllMovementSteps(step, minimum_step, loc_to_alter, velocity_to_alter, false, overlap_dir);
}
void Components::RigidbodyComponent::TryAllMovementSteps(double full_step, double minimum_step, float &location_to_alter, float &velocity_to_alter, bool x_step, Components::OverlapDirection overlap_dir)
{
    auto steps_left = full_step;
    auto step_speed = (steps_left > 0) ? 1 : -1;
    bool collision = false;

    while ((steps_left >= minimum_step || steps_left <= -minimum_step) && !collision)
    {
        double move_step = 0;
        if (steps_left > 0)
            move_step = (steps_left >= step_speed) ? step_speed : steps_left;
        else
            move_step = (steps_left <= step_speed) ? step_speed : steps_left;
        // auto move_step = (full_step >= step_speed) ? step_speed : friction_stepfull_step;
        auto box_location = box_collider->GetCurrentSdlRect();
        SDL_FRect float_rect;
        float_rect.x = box_location.x;
        float_rect.y = box_location.y;
        float_rect.w = box_location.w;
        float_rect.h = box_location.h;
        auto box_loc_to_change = (x_step) ? &float_rect.x : &float_rect.y;
        *box_loc_to_change += move_step;

        collision = TryMovementStep(float_rect, overlap_dir);
        if (collision)
        {
            velocity_to_alter = 0;
            if (!x_step && step_speed > 0)
            {
                on_ground = true;
            }
            if (x_step)
            {
                is_moving_x = false;
            }
            break;
        }
        location_to_alter += move_step;
        steps_left -= move_step;
    }
    // Returns if we are on the ground, useful for y conversions as this will set that variable.
    // If it is not x direction, and there is a collision, and we are moving downward.
    // TODO do this differently.

    if (on_ground && !collision && !x_step)
    {
        SDL_FRect float_rect;
        auto box_location = box_collider->GetCurrentSdlRect();
        float_rect.x = box_location.x;
        float_rect.y = box_location.y;
        float_rect.w = box_location.w;
        float_rect.h = box_location.h;
        auto box_loc_to_change = (x_step) ? &float_rect.x : &float_rect.y;
        *box_loc_to_change += 0.1f;
        collision = TryMovementStep(float_rect, overlap_dir);
        if (!collision)
        {
            on_ground = false;
        }
    }
}

bool Components::RigidbodyComponent::TryMovementStep(SDL_FRect &rect, Components::OverlapDirection overlap_dir)
{
    auto solid_tiles = owner_->GetLevel()->solid_tiles;
    for (auto tile : solid_tiles)
    {
        auto tile_rect = tile->box_collider_component->rectangle.sdl_rectangle;
        SDL_FRect float_rect;
        float_rect.x = tile_rect.x;
        float_rect.y = tile_rect.y;
        float_rect.w = tile_rect.w;
        float_rect.h = tile_rect.h;

        if (SDL_HasIntersectionF(&rect, &float_rect))
        {
            return true;
        }
    }
    auto actors = owner_->GetLevel()->actors;
    for (auto actor : actors)
    {
        if (actor->id == owner_->id)
            continue;
        // auto actor_rects = actor->GetBoxCollider();
        auto actor_rects = actor->GetBoxColliders();

        for (auto &&actor_rect : actor_rects)
        {
            if (!actor_rect->is_blocking)
            // if (!actor_rects.is_blocking)
                continue;
            auto sdl_actor_rect = actor_rect->rectangle.sdl_rectangle;
            // auto sdl_actor_rect = actor_rects.rectangle.sdl_rectangle;
            SDL_FRect float_rect;
            float_rect.x = sdl_actor_rect.x;
            float_rect.y = sdl_actor_rect.y;
            float_rect.w = sdl_actor_rect.w;
            float_rect.h = sdl_actor_rect.h;

            if (SDL_HasIntersectionF(&rect, &float_rect))
            {
                box_collider->AddToOverlaps(actor_rect);
                auto overlap_start = std::find(box_collider->last_frame_overlaps.begin(), box_collider->last_frame_overlaps.end(), actor_rect->id);
                if (overlap_start == box_collider->last_frame_overlaps.end())
                {
                    auto args = Components::BoxColliderEventArgs(owner_, overlap_dir);
                    actor_rect->OnOverlapBeginEvent(args);
                }
                return true;
            }
        }
    }
    return false;
}

bool Components::RigidbodyComponent::TryActorStep(SDL_FRect &rect)
{
    auto actors = owner_->GetLevel()->actors;
    for (auto actor : actors)
    {
        if (actor->id == owner_->id)
            continue;
        auto actor_rects = actor->GetBoxColliders();

        for (auto &&actor_rect : actor_rects)
        {
            if (actor_rect->is_blocking)
                continue;
            auto sdl_actor_rect = actor_rect->rectangle.sdl_rectangle;
            SDL_FRect float_rect;
            float_rect.x = sdl_actor_rect.x;
            float_rect.y = sdl_actor_rect.y;
            float_rect.w = sdl_actor_rect.w;
            float_rect.h = sdl_actor_rect.h;

            if (SDL_HasIntersectionF(&rect, &float_rect))
            {
                box_collider->AddToOverlaps(actor_rect);
                auto overlap_start = std::find(box_collider->last_frame_overlaps.begin(), box_collider->last_frame_overlaps.end(), actor_rect->id);
                if (overlap_start == box_collider->last_frame_overlaps.end())
                {
                    auto args = Components::BoxColliderEventArgs(owner_, OverlapDirection::Default);
                    actor_rect->OnOverlapBeginEvent(args);
                }
            }
            return true;
        }
    }
    return false;
}

void Components::RigidbodyComponent::ApplyForce(Vector2 force)
{
    acceleration += force;
}
