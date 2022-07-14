#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>

Tile::Tile(Vector2 loc, std::shared_ptr<SDL_Texture> texture, Rectangle src_rect, int layer, bool is_solid) : GameObject{loc}
{
    sprite_component_ = new Components::SpriteComponent(this, texture, src_rect, layer);
    if (is_solid)
        box_collider_component = new Components::BoxColliderComponent(this, src_rect.GetSize());
}

Tile::~Tile()
{
}