#include <supergoon_engine/engine/component.hpp>

Component::Component(GameObject *owner, Vector2 offset)
{
    offset_ = offset;
    owner_ = owner;
}

Component::~Component()
{

}