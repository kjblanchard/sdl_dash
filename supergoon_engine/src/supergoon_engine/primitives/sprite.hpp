#pragma once
#include <supergoon_engine_export.h>
#include <memory>

struct SDL_Texture;

enum class SpriteFlip
{
    Default,
    Horizontal,
    Vertical
};
struct SUPERGOON_ENGINE_EXPORT Sprite
{
    Sprite(std::shared_ptr<SDL_Texture> texture_ptr);
    ~Sprite();
    // bool mirror = false;
    SpriteFlip flip = SpriteFlip::Default;
    std::shared_ptr<SDL_Texture> texture;
};