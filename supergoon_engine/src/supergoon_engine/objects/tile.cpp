#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>


Tile::Tile(Vector2 loc,std::shared_ptr<SDL_Texture> texture, Rectangle src_rect ) : GameObject{loc}
{
    sprite_component_ = new Components::SpriteComponent(this,texture,src_rect);
    box_collider_component = new Components::BoxColliderComponent(this,src_rect.size);
}

Tile::~Tile()
{
}