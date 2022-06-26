#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/components/sprite_component.hpp>


Tile::Tile(Vector2 loc, const char* filename, Rectangle src_rect ) : GameObject{loc}
{
    sprite_component_ = new SpriteComponent(this,filename,src_rect);
    AddComponent(sprite_component_);
}

Tile::~Tile()
{
}