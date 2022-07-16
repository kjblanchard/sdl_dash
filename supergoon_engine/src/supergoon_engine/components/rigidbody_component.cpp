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
    std::cout << "Velocity| X: " << velocity.x << " Y: " << velocity.y << std::endl;
    if (gravity_enabled)
        Gravity::ApplyGravity(*this, owner_->GetLevel()->gravity_params, gametime);
    ApplyVelocity(gametime);
}

void Components::RigidbodyComponent::ApplyVelocity(const Gametime &gametime)
{
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
    auto thing = TryAllMovementSteps(step, minimum_step, loc_to_alter, velocity_to_alter);

}
void Components::RigidbodyComponent::ApplyVelocityByStepSolidsY(double step)
{
    auto minimum_step = minimum_y_step;
    auto &loc_to_alter = owner_->location.y;
    auto &velocity_to_alter = velocity.y;
    auto thing = TryAllMovementSteps(step, minimum_step, loc_to_alter, velocity_to_alter);

}
bool Components::RigidbodyComponent::TryAllMovementSteps(double full_step, double minimum_step, float& location_to_alter, float& velocity_to_alter)
{
    auto step_speed = (full_step > 0) ? 1 : -1;
    bool collision = false;

    while (full_step >= minimum_step || full_step <= -minimum_step)
    {
        auto move_step = (full_step >= step_speed) ? 1 : full_step;
        auto box_location = box_collider->GetCurrentSdlRect();
        box_location.x += move_step;
        collision = TryMovementStep(box_location);
        if (collision)
        {
            velocity_to_alter = 0;
            break;
        }
        location_to_alter += move_step;
        full_step -= move_step;
    }
}

bool Components::RigidbodyComponent::TryMovementStep(SDL_Rect &rect)
{
    auto solid_tiles = owner_->GetLevel()->solid_tiles;
    for (auto tile : solid_tiles)
    {
        auto tile_rect = tile->box_collider_component->rectangle.sdl_rectangle;
        if (SDL_HasIntersection(&rect, &tile_rect))
        {
            return true;
        }
    }
    return false;
}

void Components::RigidbodyComponent::ApplyForce(Vector2 force, Vector2 constraint)
{
    auto temp_velocity = velocity + force;
    velocity = temp_velocity;
}
