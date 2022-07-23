#include <supergoon_engine/graphics/sprite_batch.hpp>
#include <supergoon_engine/graphics/graphics_device.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/primitives/sprite.hpp>
#include <ostream>
#include <fstream>
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
    draw_rects.clear();
}

void SpriteBatch::Draw(Sprite &sprite, Rectangle &dst_rect, Rectangle &src_rect, int layer)
{
    auto draw_object = DrawObject{};
    draw_object.sprite = &sprite;
    draw_object.dst_rect = &dst_rect;
    draw_object.src_rect = &src_rect;
    draw_object.layer = layer;
    draw_objects.push_back(draw_object);
}


void SpriteBatch::End()
{

    std::sort(draw_objects.begin(), draw_objects.end(), [](DrawObject &lhs, DrawObject &rhs)
              { return lhs.layer < rhs.layer; });

    SDL_SetRenderDrawColor(
        graphics_device->renderer,
        255,
        0,
        0,
        255);
    for (auto &&i : draw_objects)
    {
        if (!i.sprite)
        {
            SDL_RenderDrawRectF(graphics_device->renderer, &i.dst_rect->sdl_rectangle);
        }
        else
        {
            auto mirror = (i.sprite->mirror) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            auto src_rect = i.src_rect->GetRect();
            SDL_RenderCopyExF(
                graphics_device->renderer,
                i.sprite->texture.get(),
                &src_rect,
                &i.dst_rect->sdl_rectangle,
                0.0,
                NULL,
                mirror
                );
        }
    }

    SDL_SetRenderDrawColor(
        graphics_device->renderer,
        0,
        0,
        0,
        255);

    SDL_RenderPresent(graphics_device->renderer);
}
void SpriteBatch::DrawRect(Rectangle &dst_rect)
{
    auto draw_object = DrawObject{};
    draw_object.sprite = nullptr;
    draw_object.src_rect = nullptr;
    draw_object.dst_rect = &dst_rect;
    draw_object.layer = 50;
    draw_objects.push_back(draw_object);
    // draw_rects.push_back(&dst_rect);
}