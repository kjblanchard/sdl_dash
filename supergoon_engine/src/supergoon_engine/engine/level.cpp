#include <supergoon_engine/engine/level.hpp>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <supergoon_engine/tiled/tiled_loader.hpp>
#include <supergoon_engine/lua/lua_loader.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>
#include <supergoon_engine/engine/engine_tags.hpp>

Level::Level(const char *level_name, Content *content_ptr) : tilemap{nullptr}, map_name{level_name}, content{content_ptr}
{
}

Level::~Level()
{
}

void Level::Initialize()
{
    tilemap = Lua::LoadTiledMap(map_name);
    auto unsorted_tiles = Tiled::LoadTilesFromTilemap(tilemap, content);
    for (auto i : unsorted_tiles)
    {
        auto box = i->GetComponent(Tags::ComponentTags::Box);
        if (box)
        {
            solid_tiles.push_back(i);
        }
        else
        {
            tiles.push_back(i);
        }
    }
    auto actor_params = tilemap->actors;
    for (auto &&actor_param : actor_params)
    {
        auto actor = Objects::SpawnActor(actor_param);
        if (actor)
            actors.push_back(actor);
    }
}

void Level::Update(const Gametime &gametime)
{
    for (auto i : tiles)
    {
        i->Update(gametime);
    }
    for (auto i : solid_tiles)
    {
        i->Update(gametime);
    }
    for (auto i : actors)
    {
        i->Update(gametime);
    }
}

void Level::Draw(Graphics::SpriteBatch &spritebatch)
{
    for (auto i : tiles)
    {
        i->Draw(spritebatch);
    }
    for (auto i : solid_tiles)
    {
        i->Draw(spritebatch);
    }
    for (auto i : actors)
    {
        i->Draw(spritebatch);
    }
}

std::vector<std::shared_ptr<Objects::Actor>> Level::LoadActorsFromTilemap(Tiled::Tilemap *tilemap)
{
}