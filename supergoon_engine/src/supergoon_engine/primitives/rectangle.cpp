#include <supergoon_engine/primitives/rectangle.hpp>

const SDL_Rect Rectangle::GetSDL_Rect() const
{
    SDL_Rect rect;
    rect.h = size.y;
    rect.w = size.x;
    rect.x = location.x;
    rect.y = location.y;
    return rect;
}