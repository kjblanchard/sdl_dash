#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <iostream>
#include <SDL.h>


SpriteComponent::SpriteComponent(GameObject *owner) : Component(owner)
{
    texture = NULL;
}
SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(texture);
    std::cout << "Sprite component destructor called" << std::endl;
}

void SpriteComponent::Draw(SDL_Renderer *renderer)
{
    if (texture == NULL)
    {
        texture = World::GetWorld()->content->LoadTexture("purple");
    }
    SDL_Rect dst_rect;
    dst_rect.w = dst_rect.h = 16;
    dst_rect.x = dst_rect.y = 0;

    SDL_Rect src_rect;
    src_rect.w = src_rect.h = 16;
    src_rect.x = src_rect.y = 32;
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderDrawRect(renderer, &dst_rect);
    SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}