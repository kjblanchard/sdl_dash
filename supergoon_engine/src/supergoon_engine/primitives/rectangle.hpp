#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/primitives/point.hpp>
#include <SDL_rect.h>


/**
 * Data type that holds two ints
 *
 * Holds a x and y value of ints.  Can be converted to Vector 2.  This should be used for things that draw to the screen.
 */
struct SUPERGOON_ENGINE_EXPORT Rectangle
{
    Point size;
    Point location;

    Rectangle() : size{Point()}, location{Point()}{}
    Rectangle(Point loc, Point rect_size) : size{rect_size}, location{loc}{}

    /**
     * Makes a new SDL_Rect from this rectangle
     *
     * @return Creates a new vector 2 based on this class.
     */
    SDL_Rect GetSDL_Rect();
};
