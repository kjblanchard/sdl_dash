#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>

struct Rectangle;
class SpriteComponent;

class Tile : public GameObject
{
private:
    /* data */
    SpriteComponent* sprite_component_;
public:
    Tile(Vector2 loc, const char* filename, Rectangle src_rect);
    ~Tile() override;
};

