#include <supergoon_engine/primitives/vector2.hpp>
#include <supergoon_engine/primitives/point.hpp>

Point Vector2::ToPoint()
{
    return Point(x,y);
}