#include <supergoon_engine/primitives/sprite.hpp>
#include <SDL.h>

Sprite::Sprite(std::shared_ptr<SDL_Texture> texture_ptr) : texture{texture_ptr}
{
}

Sprite::~Sprite()
{
}