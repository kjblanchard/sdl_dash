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
}
SpriteComponent::SpriteComponent(GameObject *owner, std::shared_ptr<SDL_Texture> texture, Rectangle src_rectangle) : Component(owner), sprite{Sprite(texture)}
{
    src_rect_ = src_rectangle;
    dst_rect_ = Rectangle{owner->location.ToPoint(), src_rectangle.size};
}
SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Initialize()
{
}

void SpriteComponent::Update(const Gametime &gametime)
{
    dst_rect_.location.x = static_cast<int>((static_cast<double>(owner_->location.x + offset_.x)) * main_camera->GetResolutionScaleSizeX());
    dst_rect_.location.y = static_cast<int>((static_cast<double>(owner_->location.y + offset_.y)) * main_camera->GetResolutionScaleSizeY());
}

void SpriteComponent::Draw(SDL_Renderer *renderer)
{

    auto dst_rect = dst_rect_.GetSDL_Rect();
    auto src_rect = src_rect_.GetSDL_Rect();
    dst_rect.x -= main_camera->rect.x;
    dst_rect.y -= main_camera->rect.y;
    // Scale to resolution size manually.
    dst_rect.w *= main_camera->GetResolutionScaleSizeX();
    dst_rect.h *= main_camera->GetResolutionScaleSizeY();

    SDL_RenderCopy(renderer, sprite.texture.get(), &src_rect, &dst_rect);
}
void SpriteComponent::UpdateFromAnimationComponent(Rectangle src_rectangle)
{
    src_rect_ = src_rectangle;
}