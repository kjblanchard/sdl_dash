#include <supergoon_engine/physics/gravity.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>

void Gravity::ApplyGravity(Components::RigidbodyComponent &rb, GravityParams &gravity_params, const Gametime &gametime)
{
    auto gravity_step = gravity_params.gravity * gametime.ElapsedTimeInSeconds();
    auto friction_step = rb.velocity.x * gravity_params.friction * gametime.ElapsedTimeInSeconds() * 2.0;

    GravityConstraintY(rb, gravity_params, gravity_step);
    GravityConstraintX(rb, gravity_params, friction_step);
}

void Gravity::GravityConstraintY(Components::RigidbodyComponent &rb, GravityParams &params, double gravity_step)
{
    if (!params.enabled)
        return;
    auto desired_velocity_y = rb.velocity.y + gravity_step;
    if (desired_velocity_y > 0)
    {
        desired_velocity_y = (desired_velocity_y > params.max_velocity.y) ? rb.velocity.y : desired_velocity_y;
        desired_velocity_y = (desired_velocity_y < params.min_velocity.y) ? 0 : desired_velocity_y;
    }
    if (desired_velocity_y < 0)
    {
        desired_velocity_y = (desired_velocity_y < -params.max_velocity.y) ? -params.max_velocity.y : desired_velocity_y;
        desired_velocity_y = (desired_velocity_y > -params.min_velocity.y) ? 0 : desired_velocity_y;
    }
    rb.velocity.y = desired_velocity_y;
}

void Gravity::GravityConstraintX(Components::RigidbodyComponent &rb, GravityParams &params, double friction_step)
{
    if (rb.accel_applied_this_frame)
        return;
    auto desired_velocity_x = rb.velocity.x - friction_step;

    if (desired_velocity_x > 0)
    {

        desired_velocity_x = (desired_velocity_x > params.max_velocity.x) ? params.max_velocity.y : desired_velocity_x;
        desired_velocity_x = (desired_velocity_x < params.min_velocity.x) ? 0 : desired_velocity_x;
    }
    if (desired_velocity_x < 0)
    {
        desired_velocity_x = (desired_velocity_x < -params.max_velocity.x) ? -params.max_velocity.y : desired_velocity_x;
        desired_velocity_x = (desired_velocity_x > -params.min_velocity.x) ? 0 : desired_velocity_x;
    }
    rb.velocity.x = desired_velocity_x;
}
