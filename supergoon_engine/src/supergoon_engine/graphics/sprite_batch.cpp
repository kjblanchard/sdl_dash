#include <supergoon_engine/graphics/sprite_batch.hpp>
#include <supergoon_engine/graphics/graphics_device.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/primitives/sprite.hpp>
#include <SDL.h>

using namespace Graphics;

SpriteBatch::SpriteBatch(GraphicsDevice *graphics)
{
    graphics_device = graphics;
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::Begin()
{
    SDL_SetRenderDrawColor(graphics_device->renderer, 21, 21, 21, 255);
    SDL_RenderClear(graphics_device->renderer);
    draw_objects.clear();
}

void SpriteBatch::Draw(Sprite &sprite, Rectangle &dst_rect, Rectangle &src_rect)
{
    auto draw_object = DrawObject{};
    draw_object.sprite = &sprite;
    draw_object.dst_rect = &dst_rect;
    draw_object.src_rect = &src_rect;
    draw_objects.push_back(draw_object);
}

void SpriteBatch::End()
{
    for (auto &&i : draw_objects)
    {
        SDL_RenderCopy(
            graphics_device->renderer,
            i.sprite->texture.get(),
            &i.src_rect->sdl_rectangle,
            &i.dst_rect->sdl_rectangle
        );
    }

    SDL_RenderPresent(graphics_device->renderer);
}