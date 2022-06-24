#include <supergoon_engine/engine/gameobject.hpp>
#include <SDL_image.h>
#include <iostream>
#include <SDL.h>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/engine/content.hpp>

// statics
World *GameObject::world = nullptr;

GameObject::GameObject(Vector2 loc) : location{loc}
{
    texture = NULL;
}
GameObject::~GameObject()
{
    SDL_DestroyTexture(texture);
}
void GameObject::Update(const Gametime &gametime)
{
    std::cout << "My location is X: " << location.x << "Y: " << location.y << std::endl;
    std::cout << "Total gametime is " << gametime.DeltaTime() << std::endl;
}

void GameObject::Draw(SDL_Renderer *renderer)
{
    if (texture == NULL)
    {
        texture = world->content->LoadTexture("purple");
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