#include <supergoon_engine/primitives/vector2.hpp>
#include <supergoon_engine/primitives/point.hpp>
#include <cmath>

Point Vector2::ToPoint()
{
    //Doesn't seem to do much on its own.
    return Point(round(x),round(y));
}