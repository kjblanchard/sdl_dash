#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/primitives/point.hpp>

class GameObject;
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
    };
}