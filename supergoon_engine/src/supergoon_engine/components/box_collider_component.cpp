#include <supergoon_engine/components/box_collider_component.hpp>

Components::BoxColliderComponent::BoxColliderComponent(GameObject *owner, Point box_size, Vector2 offset) : Component{owner, offset}, size{box_size}
{
}

Components::BoxColliderComponent::~BoxColliderComponent()
{
}
void Components::BoxColliderComponent::Update(const Gametime &gametime)
{
    rectangle.sdl_rectangle.x = (owner_->location.x + static_cast<int>(offset_.x)) * main_camera->GetResolutionScaleSizeX();
    rectangle.sdl_rectangle.y = (owner_->location.y + static_cast<int>(offset_.y)) * main_camera->GetResolutionScaleSizeY();
    rectangle.sdl_rectangle.w = size.x * main_camera->GetResolutionScaleSizeX();
    rectangle.sdl_rectangle.h = size.y * main_camera->GetResolutionScaleSizeY();
}

void Components::BoxColliderComponent::Draw(Graphics::SpriteBatch &spritebatch)
{
    // SDL_RenderDrawRect(render, &rectangle.sdl_rectangle);
}