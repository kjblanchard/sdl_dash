#pragma once
#include <supergoon_engine/primitives/gametime.hpp>
#include <supergoon_engine/primitives/vector2.hpp>

class RigidbodyComponent;

namespace Gravity
{
    class GravityParams
    {
    public:
        int gravity = 0;
        int friction = 0;
        Vector2 min_velocity;
        Vector2 max_velocity;
    };

    void ApplyGravity(RigidbodyComponent &rb, GravityParams &gravity_params, Gametime &gametime);
    static void GravityConstraintX();
    static void GravityConstraintY();

}