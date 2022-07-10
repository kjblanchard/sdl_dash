#pragma once
#include <supergoon_engine/primitives/rectangle.hpp>

namespace Aseprite
{
    struct AsepriteFrame
    {
        unsigned int frame_num;
        Rectangle source_rect;
        unsigned int millisecond_length;

        inline bool operator<(const AsepriteFrame &rhs) const
        {
            return frame_num < rhs.frame_num;
        }
        inline bool operator<=(const AsepriteFrame &rhs) const
        {
            return frame_num <= rhs.frame_num;
        }
        inline bool operator==(const AsepriteFrame &rhs) const
        {
           return frame_num == rhs.frame_num;
        }
        inline bool operator>(const AsepriteFrame &rhs) const
        {
            return frame_num > rhs.frame_num;
        }
        inline bool operator>=(const AsepriteFrame &rhs) const
        {
            return frame_num >= rhs.frame_num;
        }
    };
}