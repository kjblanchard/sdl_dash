#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <SDL_rect.h>

SpriteComponent::SpriteComponent(GameObject *owner, SDL_Texture* texture, Point size, Point src_loc) : Component(owner)
{
    this->texture = texture;
    src_rect_ = Rectangle{src_loc, size};
    dst_rect_ = Rectangle{owner->location.ToPoint(), size};
}
SpriteComponent::SpriteComponent(GameObject *owner, SDL_Texture* texture, Rectangle src_rectangle) : Component(owner)
{
    this->texture = texture;
    src_rect_ = src_rectangle;
    dst_rect_ = Rectangle{owner->location.ToPoint(), src_rectangle.size};
}
SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(texture);
}

void SpriteComponent::Initialize()
{

}

void SpriteComponent::Update(const Gametime &gametime)
{
    dst_rect_.location.x = static_cast<int>(owner_->location.x + offset_.x);
    dst_rect_.location.y = static_cast<int>(owner_->location.y + offset_.y);
}

void SpriteComponent::Draw(SDL_Renderer *renderer)
{
    auto cam = World::GetWorld()->camera;
    auto dst_rect = dst_rect_.GetSDL_Rect();
    auto src_rect = src_rect_.GetSDL_Rect();
    dst_rect.x -= cam.x;
    dst_rect.y -= cam.y;

    SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}