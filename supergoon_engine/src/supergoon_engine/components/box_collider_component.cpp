#include <supergoon_engine/components/box_collider_component.hpp>
#include <supergoon_engine/graphics/sprite_batch.hpp>
#include <supergoon_engine/engine/engine_tags.hpp>

Components::BoxColliderComponent::BoxColliderComponent(GameObject *owner, Point box_size, Vector2 offset) : Component{owner, offset}, rectangle{Point(owner->location.x + offset.x, owner->location.y + offset.y), box_size}
{
    AddTag(Tags::ComponentTags::Box);
}

Components::BoxColliderComponent::~BoxColliderComponent()
{
}
SDL_Rect Components::BoxColliderComponent::GetCurrentSdlRect()
{
    SDL_Rect rect;
    rect.x = owner_->location.x + offset_.x;
    rect.y = owner_->location.y + offset_.y;
    rect.w = rectangle.GetSize().x;
    rect.h = rectangle.GetSize().y;
    return rect;
}
void Components::BoxColliderComponent::Update(const Gametime &gametime)
{
    rectangle.sdl_rectangle.x = (owner_->location.x + static_cast<int>(offset_.x)) ;
    rectangle.sdl_rectangle.y = (owner_->location.y + static_cast<int>(offset_.y)) ;
}

void Components::BoxColliderComponent::Draw(Graphics::SpriteBatch &spritebatch)
{
    if (!debug)
        return;
    temp_rect = rectangle;
    temp_rect.sdl_rectangle.x = temp_rect.sdl_rectangle.x * main_camera->GetResolutionScaleSizeX() -  main_camera->rect.x;
    temp_rect.sdl_rectangle.y = temp_rect.sdl_rectangle.y *  main_camera->GetResolutionScaleSizeY() - main_camera->rect.y;
    temp_rect.sdl_rectangle.w *= main_camera->GetResolutionScaleSizeX();
    temp_rect.sdl_rectangle.h *= main_camera->GetResolutionScaleSizeY();
    spritebatch.DrawRect(temp_rect);
}