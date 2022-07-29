#pragma once
#include <vector>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/aseprite/aseprite_frame.hpp>
#include <supergoon_engine/aseprite/aseprite_animation.hpp>
#include <memory>

struct SDL_Texture;

namespace Aseprite
{
    /**
     * Holds all the Aseprite frames (animation points) and Animation(ms per frame and tags) and the loaded texture for a aseprite file.
     */
    class AsepriteSheet
    {
    public:
        AsepriteSheet(const char *file_name);

        Point sheet_size;
        std::vector<AsepriteFrame> sprite_sheet_frames;
        std::vector<AsepriteAnimation> sprite_sheet_animations;
        std::shared_ptr<SDL_Texture> texture;
    };
}