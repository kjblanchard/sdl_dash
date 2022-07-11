#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>

struct Rectangle;

namespace Components
{

    class SpriteComponent;
    class BoxColliderComponent;
}

class Tile : public GameObject
{
private:
    /* data */
    Components::SpriteComponent *sprite_component_;
    Components::BoxColliderComponent* box_collider_component;

public:
    Tile(Vector2 loc,std::shared_ptr<SDL_Texture>texture, Rectangle src_rect);
    ~Tile() override;
};
