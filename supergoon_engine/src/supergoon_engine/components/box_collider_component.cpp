#include <supergoon_engine/components/box_collider_component.hpp>
#include <supergoon_engine/graphics/sprite_batch.hpp>

Components::BoxColliderComponent::BoxColliderComponent(GameObject *owner, Point box_size, Vector2 offset) : Component{owner, offset}, rectangle{Point(owner->location.x + offset.x, owner->location.y + offset.y), box_size}
{
}

Components::BoxColliderComponent::~BoxColliderComponent()
{
}
void Components::BoxColliderComponent::Update(const Gametime &gametime)
{
    rectangle.sdl_rectangle.x = (owner_->location.x + static_cast<int>(offset_.x)) * main_camera->GetResolutionScaleSizeX();
    rectangle.sdl_rectangle.y = (owner_->location.y + static_cast<int>(offset_.y)) * main_camera->GetResolutionScaleSizeY();
}

void Components::BoxColliderComponent::Draw(Graphics::SpriteBatch &spritebatch)
{
    if (!debug)
        return;
    temp_rect = rectangle;
    temp_rect.sdl_rectangle.x -= main_camera->rect.x;
    temp_rect.sdl_rectangle.y -= main_camera->rect.y;
    temp_rect.sdl_rectangle.w *= main_camera->GetResolutionScaleSizeX();
    temp_rect.sdl_rectangle.h *= main_camera->GetResolutionScaleSizeY();
    spritebatch.DrawRect(temp_rect);
}