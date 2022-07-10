#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>

struct Rectangle;

namespace Components
{

    class SpriteComponent;
}

class Tile : public GameObject
{
private:
    /* data */
    Components::SpriteComponent *sprite_component_;

public:
    Tile(Vector2 loc,std::shared_ptr<SDL_Texture>texture, Rectangle src_rect);
    ~Tile() override;
};