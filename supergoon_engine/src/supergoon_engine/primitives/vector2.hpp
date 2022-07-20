#pragma once
#include <supergoon_engine_export.h>

struct Point;

/**
 * A data type that holds two floats, x and y
 *
 * Has conversion to point.  Vector 2 can hold decimal places, and should not be used for things that draw, should be converted first.
 */
struct SUPERGOON_ENGINE_EXPORT Vector2

{
    double x = 0;
    double y = 0;

    Vector2()
    {
        x = y = 0;
    }
    Vector2(float xy)
    {
        x = y = xy;
    }
    Vector2(float x_, float y_)
    {
        x = x_;
        y = y_;
    }
    inline Vector2 &operator+=(const Vector2 &rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    inline Vector2 operator+(const Vector2 &rhs) const
    {
        return Vector2(x + rhs.x, y + rhs.y);
    }
    inline bool operator==(const Vector2 rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    inline bool operator!=(const Vector2 rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

    inline static Vector2 Zero()
    {
        return Vector2();
    }

    /**
     * Makes a new point with the values from the vec2.  Decimal places will be lost (does not round.)
     *
     * @return A new point with the x y values from this vector2
     */
    Point ToPoint();
};
