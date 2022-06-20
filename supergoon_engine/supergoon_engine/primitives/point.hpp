#pragma once
#include <supergoon_engine_export.h>

struct Vector2;

/**
 * Data type that holds two ints
 *
 * Holds a x and y value of ints.  Can be converted to Vector 2.  This should be used for things that draw to the screen.
 */
struct SUPERGOON_ENGINE_EXPORT Point
{
    int x = 0;
    int y = 0;

    Point() : x{0}, y{0} {}
    Point(int xy) : x{xy}, y{xy} {}
    Point(int x_, int y_) : x{x_}, y{y_} {}

    /**
     * Makes a new vector2 from this point
     *
     * @return Creates a new vector 2 based on this class.
     */
    Vector2 ToVector2();
};
