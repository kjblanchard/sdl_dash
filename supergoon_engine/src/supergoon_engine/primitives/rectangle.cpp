#include <supergoon_engine/primitives/rectangle.hpp>

SDL_Rect Rectangle::GetSDL_Rect()
{
    SDL_Rect rect;
    rect.h = size.y;
    rect.w = size.x;
    rect.x = location.x;
    rect.y = location.y;
    return rect;
}