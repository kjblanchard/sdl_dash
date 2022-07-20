#pragma once
#include <supergoon_engine_export.h>
#include <limits>
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/primitives/point.hpp>

class GameObject;
class Tile;

namespace Components
{
    class BoxColliderComponent;

    class SUPERGOON_ENGINE_EXPORT RigidbodyComponent : public Component
    {
    private:
        BoxColliderComponent *box_collider;
        const double minimum_y_step = 0.2;
        const double minimum_x_step = 0.2;
        bool gravity_enabled = true;

    public:
        RigidbodyComponent(GameObject *owner, Point box_size, Vector2 offset = Vector2());
        ~RigidbodyComponent() override;
        void Update(const Gametime &) override;
        void ApplyVelocity(const Gametime &);
        void ApplyVelocityByStepSolidsX(double step);
        void ApplyVelocityByStepSolidsY(double step);
        void TryAllMovementSteps(double full_step, double minimum_step, double& location_to_alter, double& velocity_to_alter, bool x_step);
        bool TryMovementStep(SDL_FRect& rect_to_check);
        void ApplyForce(Vector2 force);
        Vector2 max_velocity = Vector2(std::numeric_limits<float>::max());
        Vector2 velocity = Vector2();
        bool accel_applied_this_frame = false;
        bool on_ground = false;
        Vector2 acceleration = Vector2();
    };
}