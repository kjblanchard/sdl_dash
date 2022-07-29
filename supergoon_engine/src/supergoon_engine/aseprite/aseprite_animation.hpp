#pragma once
#include <supergoon_engine/primitives/rectangle.hpp>
#include <string>

namespace Aseprite
{
    /**
     * A aseprite animation, which is a "tag" within aseprite, and the frame it begins and ends on.
     */
    struct AsepriteAnimation
    {
        std::string name;
        int frame_begin;
        int frame_end;
    };
}