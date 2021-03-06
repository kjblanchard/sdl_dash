#pragma once
#include <vector>
#include <string>
#include <memory>
#include <sol2/forward.hpp>
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gravity.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/objects/actor.hpp>
#include <supergoon_engine/interfaces/i_initialize.hpp>
#include <supergoon_engine/interfaces/i_update.hpp>
#include <supergoon_engine/interfaces/i_draw.hpp>

    class Tile;
namespace Tiled
{
    class Tilemap;
}
class Content;

class Level : public IInitialize, public IUpdate, public IDraw

{
private:
    Tiled::Tilemap *tilemap;
    std::string map_name;
    Content* content;

    // std::vector<std::shared_ptr<Objects::Actor>>
    // LoadActorsFromTilemap(Tiled::Tilemap *tilemap);

public:
    Level(sol::table& current_level_table, Content* content_ptr);
    ~Level() override;

    //TODO make this in a namespace, or not static here.
    static Vector2 current_level_size;
    std::vector<Tile*> tiles;
    std::vector<Tile*> solid_tiles;
    std::vector<Objects::Actor*> actors;
    Gravity::GravityParams gravity_params;

    void Initialize() override;
    void Update(const Gametime &gametime) override;
    void Draw(Graphics::SpriteBatch &spritebatch) override;
};