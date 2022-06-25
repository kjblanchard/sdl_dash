#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>

// class SUPERGOON_ENGINE_EXPORT SpriteComponent : public Component
class SpriteComponent : public Component
{
private:
public:
    Rectangle dst_rect_;
    Rectangle src_rect_;
    SDL_Texture *texture;

public:
    SpriteComponent(GameObject *owner, const char* filename, Point size = Point(), Point src_loc = Point());
    SpriteComponent(GameObject *owner, const char* filename, Rectangle src_rectangle);
    ~SpriteComponent();
    void Update(const Gametime &gametime) override;
    void Draw(SDL_Renderer *renderer) override;
};
