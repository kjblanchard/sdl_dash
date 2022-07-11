#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>

Components::RigidbodyComponent::RigidbodyComponent(GameObject *owner, Point box_size, Vector2 offset) : Component{owner, offset}
{
    box_collider = new BoxColliderComponent(owner, box_size, offset);
}

Components::RigidbodyComponent::~RigidbodyComponent()
{

}
