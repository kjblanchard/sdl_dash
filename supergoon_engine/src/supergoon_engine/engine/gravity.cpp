#include <supergoon_engine/engine/gravity.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>

void Gravity::ApplyGravity(Components::RigidbodyComponent &rb, GravityParams &gravity_params, const Gametime &gametime)
{
    auto gravityStep = gravity_params.gravity * gametime.ElapsedTimeInSeconds();
    GravityConstraintY(rb, gravity_params, gravityStep);
}

void Gravity::GravityConstraintY(Components::RigidbodyComponent &rb, GravityParams &params, double gravity_step)
{
    if (!params.enabled)
        return;
    auto desired_velocity_y = rb.velocity.y + gravity_step;
    if (desired_velocity_y > 0)
    {
        desired_velocity_y = (desired_velocity_y > params.max_velocity.y) ? params.max_velocity.y : desired_velocity_y;
        desired_velocity_y = (desired_velocity_y < params.min_velocity.y) ? 0 : desired_velocity_y;
    }
    if (desired_velocity_y < 0)
    {
        desired_velocity_y = (desired_velocity_y > -params.max_velocity.y) ? -params.max_velocity.y : desired_velocity_y;
        desired_velocity_y = (desired_velocity_y < -params.min_velocity.y) ? 0 : desired_velocity_y;
    }
}
