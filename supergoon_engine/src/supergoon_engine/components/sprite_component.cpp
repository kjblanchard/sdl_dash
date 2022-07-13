#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <supergoon_engine/objects/camera.hpp>
#include <supergoon_engine/aseprite/aseprite_sheet.hpp>
#include <SDL_rect.h>

using namespace Components;

SpriteComponent::SpriteComponent(GameObject *owner, std::shared_ptr<SDL_Texture> texture, Point size, Point src_loc) : Component(owner), sprite{Sprite(texture)}
{
    src_rect_ = Rectangle{src_loc, size};
    dst_rect_ = Rectangle{owner->location.ToPoint(), size};
    temp_dst_rect = Rectangle{owner->location.ToPoint(), size};
}
SpriteComponent::SpriteComponent(GameObject *owner, std::shared_ptr<SDL_Texture> texture, Rectangle src_rectangle) : Component(owner), sprite{Sprite(texture)}
{
    src_rect_ = src_rectangle;
    dst_rect_ = Rectangle{owner->location.ToPoint(), src_rectangle.GetSize()};
    temp_dst_rect = Rectangle{owner->location.ToPoint(), src_rectangle.GetSize()};
}
SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Initialize()
{
}

void SpriteComponent::Update(const Gametime &gametime)
{
    dst_rect_.sdl_rectangle.x = static_cast<int>((static_cast<double>(owner_->location.x + offset_.x)) * main_camera->GetResolutionScaleSizeX());
    dst_rect_.sdl_rectangle.y = static_cast<int>((static_cast<double>(owner_->location.y + offset_.y)) * main_camera->GetResolutionScaleSizeY());
}

void SpriteComponent::Draw(SDL_Renderer *renderer)
{

    temp_dst_rect = dst_rect_;
    temp_dst_rect.sdl_rectangle.x -= main_camera->rect.x;
    temp_dst_rect.sdl_rectangle.y -= main_camera->rect.y;
    // Scale to resolution size manually.
    temp_dst_rect.sdl_rectangle.w *= main_camera->GetResolutionScaleSizeX();
    temp_dst_rect.sdl_rectangle.h *= main_camera->GetResolutionScaleSizeY();

    SDL_RenderCopy(renderer, sprite.texture.get(), &src_rect_.sdl_rectangle, &temp_dst_rect.sdl_rectangle);
}
void SpriteComponent::UpdateFromAnimationComponent(Rectangle src_rectangle)
{
    src_rect_ = src_rectangle;
}