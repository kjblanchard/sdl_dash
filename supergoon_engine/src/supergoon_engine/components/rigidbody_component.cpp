#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/engine/gravity.hpp>
#include <supergoon_engine/engine/level.hpp>

Components::RigidbodyComponent::RigidbodyComponent(GameObject *owner, Point box_size, Vector2 offset) : Component{owner, offset}
{
    box_collider = new BoxColliderComponent(owner, box_size, offset);
    // gravity_enabled = false;
    ApplyForce(Vector2(150, 0));
}

Components::RigidbodyComponent::~RigidbodyComponent()
{
}
void Components::RigidbodyComponent::Update(const Gametime &gametime)
{
    accel_applied_this_frame = false;
    if (acceleration.x != 0 || acceleration.y != 0)
    {
        velocity += acceleration;
        acceleration = Vector2();
        accel_applied_this_frame = true;
    }
    if (gravity_enabled)
        Gravity::ApplyGravity(*this, owner_->GetLevel()->gravity_params, gametime);
    ApplyVelocity(gametime);
}

void Components::RigidbodyComponent::ApplyVelocity(const Gametime &gametime)
{
    // Keep velocity in range.
    velocity.x = (velocity.x > max_velocity.x) ? max_velocity.x : velocity.x;
    velocity.x = (velocity.x < -max_velocity.x) ? -max_velocity.x : velocity.x;
    velocity.y = (velocity.y > max_velocity.y) ? max_velocity.y : velocity.y;
    velocity.y = (velocity.y < -max_velocity.y) ? -max_velocity.y : velocity.y;

    auto x_step = velocity.x * gametime.ElapsedTimeInSeconds();
    auto y_step = velocity.y * gametime.ElapsedTimeInSeconds();
    ApplyVelocityByStepSolidsY(y_step);
    ApplyVelocityByStepSolidsX(x_step);
}
void Components::RigidbodyComponent::ApplyVelocityByStepSolidsX(double step)
{
    auto minimum_step = minimum_x_step;
    auto &loc_to_alter = owner_->location.x;
    auto &velocity_to_alter = velocity.x;
    TryAllMovementSteps(step, minimum_step, loc_to_alter, velocity_to_alter, true);
}
void Components::RigidbodyComponent::ApplyVelocityByStepSolidsY(double step)
{
    auto minimum_step = minimum_y_step;
    auto &loc_to_alter = owner_->location.y;
    auto &velocity_to_alter = velocity.y;
    TryAllMovementSteps(step, minimum_step, loc_to_alter, velocity_to_alter, false);
}
bool Components::RigidbodyComponent::TryAllMovementSteps(double full_step, double minimum_step, float &location_to_alter, float &velocity_to_alter, bool x_step)
{
    auto step_speed = (full_step > 0) ? 1 : -1;
    bool collision = false;

    while ((full_step >= minimum_step || full_step <= -minimum_step) && !collision)
    {
        double move_step = 0;
        if (full_step > 0)
            move_step = (full_step >= step_speed) ? step_speed : full_step;
        else
            move_step = (full_step <= step_speed) ? step_speed : full_step;
        // auto move_step = (full_step >= step_speed) ? step_speed : friction_stepfull_step;
        auto box_location = box_collider->GetCurrentSdlRect();
        SDL_FRect float_rect;
        float_rect.x = box_location.x;
        float_rect.y = box_location.y;
        float_rect.w = box_location.w;
        float_rect.h = box_location.h;
        auto box_loc_to_change = (x_step) ? &float_rect.x : &float_rect.y;
        *box_loc_to_change += move_step;
        collision = TryMovementStep(float_rect);
        if (collision)
        {
            velocity_to_alter = 0;
            if (!x_step && step_speed > 0)
                on_ground = true;
            break;
        }
        location_to_alter += move_step;
        full_step -= move_step;
        if (full_step > 100 || full_step < -100)
        {
            // printf("Why");
        }
    }
    // Returns if we are on the ground, useful for y conversions as this will set that variable.
    // If it is not x direction, and there is a collision, and we are moving downward.
    // return (!x_step && collision && step_speed > 0);
}

bool Components::RigidbodyComponent::TryMovementStep(SDL_FRect &rect)
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
    return false;
}

void Components::RigidbodyComponent::ApplyForce(Vector2 force)
{
    acceleration += force;
}
