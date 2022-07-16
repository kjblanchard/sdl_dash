#pragma once
#include <supergoon_engine/primitives/gametime.hpp>
#include <supergoon_engine/primitives/vector2.hpp>

class Level;

namespace Components{
class RigidbodyComponent;

}

namespace Gravity
{
    class GravityParams
    {
    public:
        int gravity = 0;
        double friction = 0;
        bool enabled = true;
        Vector2 min_velocity;
        Vector2 max_velocity;
        Level* current_level;
    };

    void ApplyGravity(Components::RigidbodyComponent &rb, GravityParams &gravity_params, const Gametime &gametime);
    void GravityConstraintY(Components::RigidbodyComponent& rb, GravityParams& gravity_params, double gravity_step);
    void GravityConstraintX(Components::RigidbodyComponent& rb, GravityParams& gravity_params, double gravity_step);

}