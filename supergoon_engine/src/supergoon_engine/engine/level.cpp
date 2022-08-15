#include <sol2/sol.hpp>
#include <supergoon_engine/engine/level.hpp>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <supergoon_engine/tiled/tiled_loader.hpp>
#include <supergoon_engine/lua/lua_loader.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>
#include <supergoon_engine/engine/engine_tags.hpp>
#include <supergoon_engine/physics/physics.hpp>

Vector2 Level::current_level_size = Vector2();

Level::Level(sol::table &current_level_table, Content *content_ptr) : IState{current_level_table.get<int>("id")}, tilemap{nullptr}, map_name{current_level_table["name"]}, map_music{current_level_table["music"]}, content{content_ptr}
{

    // TODO make more of the gets like this so that we try and get the right type.
    gravity_params.gravity = current_level_table.get<int>("gravity");
    gravity_params.friction = current_level_table["friction"];
    gravity_params.min_velocity = Vector2(
        current_level_table["min_x_velocity"],
        current_level_table["min_y_velocity"]);
    gravity_params.max_velocity = Vector2(
        current_level_table["max_x_velocity"],
        current_level_table["max_y_velocity"]);
}

Level::~Level()
{
}

void Level::Initialize()
{
    tilemap = Lua::LoadTiledMap(map_name);
    auto map_width = tilemap->tile_width * tilemap->width;
    Level::current_level_size.x = map_width;

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
    StartMusic(map_music);
}

void Level::Update(const Gametime &gametime)
{
    for (auto &&i : actors)
    {
        Physics::ApplyPhysics(gametime, i->GetRigidbody(), solid_tiles, actors, gravity_params);
    }

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
        i->ProcessInput(gametime);
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