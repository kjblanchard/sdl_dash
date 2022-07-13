#pragma once
#include <sol2/forward.hpp>
#include <string>
#include <vector>

namespace Aseprite{
    struct AsepriteFrame;
}
namespace Tiled{
    class Tilemap;
    class TileLayer;
}

namespace Lua
{
    std::vector<Aseprite::AsepriteFrame> LoadAsepriteFrames(std::string files);
    Tiled::Tilemap* LoadTiledMap(std::string filename);
    unsigned int ParseIntFromString(std::string aseprite_key_name);
    sol::state& LoadLuaTableIntoGlobalState(const char *file_name, const char *table_name);
    sol::state* LoadLuaTableIntoTempState(const char *file_name, const char *table_name);
    sol::state* LoadLuaTableIntoTempState(const char *file_name, const char *table_name, sol::state* state_to_load_to);
    Tiled::TileLayer* LoadTileLayer(sol::table& table, int layer_depth);
    void DropLuaTable(const char* table_name);
    extern sol::state lua_global_state;
}