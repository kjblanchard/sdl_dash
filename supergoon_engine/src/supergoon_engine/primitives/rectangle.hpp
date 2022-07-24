#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/primitives/vector2.hpp>
#include <SDL_rect.h>
#include <math.h>

/**
 * Sdl_rect wrapper.
 *
 * Holds a x and y value of ints.  Can be converted to Vector 2.  This should be used for things that draw to the screen.
 */
struct SUPERGOON_ENGINE_EXPORT Rectangle
{
    SDL_FRect sdl_rectangle;

    inline Rectangle()
    {
        sdl_rectangle.x = sdl_rectangle.y = sdl_rectangle.h = sdl_rectangle.w;
    }
    inline Rectangle(Vector2 loc, Point rect_size)
    {
        sdl_rectangle.x = loc.x;
        sdl_rectangle.y = loc.y;
        sdl_rectangle.h = rect_size.y;
        sdl_rectangle.w = rect_size.x;
    }
    inline Rectangle(Point loc, Point rect_size) : Rectangle{loc.ToVector2(), rect_size}
    {
    }

    inline Point GetSize()
    {
        return Point(sdl_rectangle.w, sdl_rectangle.h);
    }
    inline Vector2 GetLocation()
    {
        return Vector2(sdl_rectangle.x, sdl_rectangle.y);
    }

    inline SDL_Rect GetRect()
    {
        SDL_Rect rect;
        rect.x = round(sdl_rectangle.x);
        rect.y = round(sdl_rectangle.y);
        rect.w = round(sdl_rectangle.w);
        rect.h = round(sdl_rectangle.h);
        return rect;
    }
};
