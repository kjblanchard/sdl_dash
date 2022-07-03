#include <supergoon_engine/graphics/sprite_batch.hpp>
#include <supergoon_engine/graphics/graphics_device.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <SDL.h>

using namespace Graphics;

SpriteBatch::SpriteBatch(GraphicsDevice* grapics)
{
    graphics_device = grapics;
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::Begin()
{
    SDL_SetRenderDrawColor(graphics_device->renderer, 21, 21, 21, 255);
    SDL_RenderClear(graphics_device->renderer);

}

void SpriteBatch::Draw(GameObject* game_object)
{
    game_object->Draw(graphics_device->renderer);

}

void SpriteBatch::End()
{
    SDL_RenderPresent(graphics_device->renderer);

}