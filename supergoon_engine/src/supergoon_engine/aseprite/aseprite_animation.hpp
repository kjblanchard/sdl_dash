#pragma once
#include <supergoon_engine/primitives/rectangle.hpp>
#include <string>

namespace Aseprite
{
    struct AsepriteAnimation
    {
        std::string name;
        int frame_begin;
        int frame_end;
    };
}