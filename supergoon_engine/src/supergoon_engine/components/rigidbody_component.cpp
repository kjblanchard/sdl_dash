#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/physics/gravity.hpp>
#include <supergoon_engine/engine/level.hpp>
#include <algorithm>

using namespace Components;

RigidbodyComponent::RigidbodyComponent(GameObject *owner, Point box_size, Vector2 offset) : Component{owner, offset, 3}
{
    box_collider = new BoxColliderComponent(owner, box_size, offset);
}

void RigidbodyComponent::Update(const Gametime &)
{
}
