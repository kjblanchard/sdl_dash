#pragma once
#include <supergoon_engine_export.h>
#include <algorithm>
#include <limits>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>

class GameObject;

namespace Components
{

    class SUPERGOON_ENGINE_EXPORT RigidbodyComponent : public Component
    {
    private:
        inline void ClampVelocity()
        {
            velocity.x = (velocity.x > 0) ? std::clamp(velocity.x, 0.f, max_velocity.x) : std::clamp(velocity.x, -max_velocity.x, 0.f);
            velocity.y = (velocity.y >= 0) ? std::clamp(velocity.y, 0.f, max_velocity.y) : std::clamp(velocity.y, -max_velocity.y, 0.f);
        }

    public:
        const double minimum_x_step = 0.2;
        const double minimum_y_step = 0.2;
        BoxColliderComponent *box_collider;
        bool gravity_enabled = true;
        inline double GetMinimumXStep() const
        {
            return minimum_x_step;
        }
        bool is_moving_x;
        RigidbodyComponent(GameObject *owner, Point box_size, Vector2 offset = Vector2());
        void Update(const Gametime &) override;

        inline void ApplyForce(Vector2 force)
        {
            acceleration += force;
        }
        inline void ChangeVelocityStatic(Vector2 new_velocity)
        {
            velocity = new_velocity;
        }
        inline void ChangeAccelStatic(Vector2 new_velocity)
        {
            acceleration = new_velocity;
        }
        Vector2 max_velocity = Vector2(std::numeric_limits<float>::max());
        Vector2 velocity = Vector2();
        bool accel_applied_this_frame = false;
        bool on_ground = false;
        Vector2 acceleration = Vector2();
        inline BoxColliderComponent &GetBoxCollider()
        {
            return *box_collider;
        }
        inline void SetGravityEnabled(bool gravity_enabled_)
        {
            gravity_enabled = gravity_enabled_;
        }
        inline void AddOverlapEvent(std::function<void(Components::BoxColliderEventArgs)> event_function)
        {
            box_collider->overlap_events.push_back(event_function);
        }

        inline void ApplyAcceleration()
        {
            accel_applied_this_frame = false;
            if (acceleration != Vector2::Zero())
            {
                velocity += acceleration;
                ClampVelocity();
                acceleration = Vector2::Zero();
                accel_applied_this_frame = true;
            }
        }

        void AddStopBoxColliderEvents();
    };
}