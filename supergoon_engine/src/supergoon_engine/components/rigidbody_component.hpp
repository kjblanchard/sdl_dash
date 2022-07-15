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

    public:
        RigidbodyComponent(GameObject *owner, Point box_size, Vector2 offset = Vector2());
        ~RigidbodyComponent() override;
        void Update(const Gametime &) override;
        void ApplyVelocity(const Gametime &);
        void ApplyYVelocity(double step, std::vector<Tile*> solid_Tiles);
        void ApplyForce(Vector2 force, Vector2 constraint = Vector2());
        Vector2 velocity;
    };
}