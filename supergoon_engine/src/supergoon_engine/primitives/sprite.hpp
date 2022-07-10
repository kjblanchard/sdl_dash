#pragma once
#include <memory>

struct SDL_Texture;

struct Sprite{
    Sprite(std::shared_ptr<SDL_Texture> texture_ptr);
    ~Sprite();
    std::shared_ptr<SDL_Texture> texture;

};