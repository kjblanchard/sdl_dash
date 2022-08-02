#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/engine/gameobject.hpp>

// statics
World *Component::world = nullptr;
Camera *Component::main_camera = nullptr;
    unsigned long int Component::current_id = 0;

Component::Component(GameObject *owner, Vector2 offset, int update_override)
{
    if (world == nullptr)
        world = World::GetWorld();
    if (main_camera == nullptr)
        main_camera = World::GetWorld()->main_camera;
    offset_ = offset;
    owner_ = owner;
    id = current_id++;
    update_order = update_override;
    owner_->AddComponent(this);
}

Vector2 Component::GetLocation()
{
    return owner_->location + offset_;
}

Component::~Component()
{
}