#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/primitives/point.hpp>

class GameObject;
class Tile;

namespace Components
{
    class BoxColliderComponent;

    class RigidbodyComponent : public Component
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
        bool TryAllMovementSteps(double full_step, double minimum_step, double& location_to_alter, double& velocity_to_alter, bool x_step);
        bool TryMovementStep(SDL_FRect& rect_to_check);
        void ApplyForce(Vector2 force, Vector2 constraint = Vector2());
        Vector2 velocity;
    };
}