#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <iostream>
#include <SDL.h>

SpriteComponent::SpriteComponent(GameObject *owner, const char *filename, Point size, Point src_loc) : Component(owner)
{
    texture = World::GetWorld()->content->LoadTexture(filename);
    src_rect_ = Rectangle{src_loc, size};
    dst_rect_ = Rectangle{owner->location.ToPoint(), size};
}
SpriteComponent::SpriteComponent(GameObject *owner, const char *filename, Rectangle src_rectangle) : Component(owner)
{
    texture = World::GetWorld()->content->LoadTexture(filename);
    src_rect_ = src_rectangle;
    dst_rect_ = Rectangle{owner->location.ToPoint(), src_rectangle.size};
}
SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(texture);
    std::cout << "Sprite component destructor called" << std::endl;
}

void SpriteComponent::Update(const Gametime &gametime)
{
    dst_rect_.location.x = (int)owner_->location.x + offset_.x;
    dst_rect_.location.y = (int)owner_->location.y + offset_.y;
}

void SpriteComponent::Draw(SDL_Renderer *renderer)
{
    if (texture == NULL)
    {
        texture = World::GetWorld()->content->LoadTexture("purple");
    }

    auto dst_rect = dst_rect_.GetSDL_Rect();
    auto src_rect = src_rect_.GetSDL_Rect();

    SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}