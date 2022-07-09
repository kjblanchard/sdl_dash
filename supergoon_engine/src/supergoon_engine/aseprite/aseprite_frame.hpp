#pragma once
#include <supergoon_engine/primitives/rectangle.hpp>

namespace Aseprite
{
    struct AsepriteFrame
    {
        unsigned int frame_num;
        Rectangle source_rect;
        unsigned int millisecond_length;
    };
}