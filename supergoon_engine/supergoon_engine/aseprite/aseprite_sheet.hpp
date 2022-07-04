#pragma once
#include <vector>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/aseprite/aseprite_frame.hpp>

struct SDL_Texture;

namespace Aseprite
{
    class AsepriteSheet
    {
        public:
        AsepriteSheet(const char* file_name);

        Point sheet_size;
        std::vector<AsepriteFrame> sprite_sheet_frames;
        SDL_Texture* texture;
    };
}