#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/engine/gameobject.hpp>

// statics
World *Component::world = nullptr;
Camera *Component::main_camera = nullptr;

Component::Component(GameObject *owner, Vector2 offset)
{
    if (world == nullptr)
        world = World::GetWorld();
    if (main_camera == nullptr)
        main_camera = World::GetWorld()->main_camera;
    offset_ = offset;
    owner_ = owner;
    owner_->AddComponent(this);
}

Component::~Component()
{
}