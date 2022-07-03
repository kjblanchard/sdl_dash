#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/engine/world.hpp>

// statics
World *Component::world = nullptr;
Camera *Component::main_camera = nullptr;

Component::Component(GameObject *owner, Vector2 offset)
{
    offset_ = offset;
    owner_ = owner;
    if (world == nullptr)
        world = World::GetWorld();
    if (main_camera == nullptr)
        main_camera = World::GetWorld()->main_camera;
}

Component::~Component()
{
}