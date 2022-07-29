#pragma once
#include <supergoon_engine/primitives/rectangle.hpp>

namespace Aseprite
{
    /**
     * A frame that has a source_rect for within the image, and the length of the image to be shown in it's animation.
     */
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