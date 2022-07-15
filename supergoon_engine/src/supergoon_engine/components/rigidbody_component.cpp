#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/engine/gravity.hpp>
#include <supergoon_engine/engine/level.hpp>

Components::RigidbodyComponent::RigidbodyComponent(GameObject *owner, Point box_size, Vector2 offset) : Component{owner, offset}
{
    box_collider = new BoxColliderComponent(owner, box_size, offset);
}

Components::RigidbodyComponent::~RigidbodyComponent()
{
}
void Components::RigidbodyComponent::Update(const Gametime &gametime)
{
    Gravity::ApplyGravity(*this, owner_->GetLevel()->gravity_params, gametime);
    ApplyVelocity(gametime);
}

void Components::RigidbodyComponent::ApplyVelocity(const Gametime &gametime)
{
    auto x_step = velocity.x * gametime.ElapsedTimeInSeconds();
    auto y_step = velocity.y * gametime.ElapsedTimeInSeconds();
    auto solid_tiles = owner_->GetLevel()->solid_tiles;
    ApplyYVelocity(y_step, solid_tiles);
}
void Components::RigidbodyComponent::ApplyYVelocity(double step, std::vector<Tile *> solid_tiles)
{
    if (step >= 1)
    {
        bool collision = false;

        while (step >= 1)
        {
            // Temporarily add 1 to Y and check for collisions
            auto box_location = box_collider->GetCurrentSdlRect();
            ++box_location.y;
            for (auto tile : solid_tiles)
            {
                if (collision)
                    return;
                auto tile_rect = tile->box_collider_component->rectangle.sdl_rectangle;
                if (SDL_HasIntersection(&box_location, &tile_rect))
                {
                    step = 0;
                    collision = true;
                    velocity.y = 0;
                }
                if (collision)
                    break;
                    owner_->location.y++;
            }

            if (collision)
                break;
            --step;
        }
        while (step <= 1)
        {
            // Temporarily add 1 to Y and check for collisions
            auto box_location = box_collider->GetCurrentSdlRect();
            --box_location.y;
            for (auto tile : solid_tiles)
            {
                if (collision)
                    return;
                auto tile_rect = tile->box_collider_component->rectangle.sdl_rectangle;
                if (SDL_HasIntersection(&box_location, &tile_rect))
                {
                    step = 0;
                    collision = true;
                    velocity.y = 0;
                }
                if (collision)
                    break;
                    owner_->location.y--;
            }

            if (collision)
                break;
            ++step;
        }
    }
}
void Components::RigidbodyComponent::ApplyForce(Vector2 force, Vector2 constraint)
{
    auto temp_velocity = velocity + force;
    // Handle X
    if (temp_velocity.x > 0)
    {
        if (temp_velocity.x > constraint.x)
            temp_velocity.x = constraint.x;
    }
    else
    {
        if (temp_velocity.x < -constraint.x)
            temp_velocity.x = -constraint.x;
    }
    if (temp_velocity.y > 0)
    {
        if (temp_velocity.y > constraint.y)
            temp_velocity.y = constraint.y;
    }
    else
    {
        if (temp_velocity.y < -constraint.y)
            temp_velocity.y = -constraint.y;
    }
    velocity = temp_velocity;
}
