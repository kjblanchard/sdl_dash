#pragma once
#include <sol2/forward.hpp>
#include <string>
#include <vector>

namespace Aseprite{
    struct AsepriteFrame;
    struct AsepriteAnimation;
    class AsepriteSheet;
}
namespace Tiled{
    class Tilemap;
    class TileLayer;
}

namespace Lua
{
    void LoadDataFromAsepriteFile(Aseprite::AsepriteSheet& aseprite_sheet, std::string file);
    std::vector<Aseprite::AsepriteFrame> LoadAsepriteFrames(sol::table& aseprite_lua_table);
    std::vector<Aseprite::AsepriteAnimation> LoadAsepriteAnimations(sol::table& aseprite_lua_table);
    Tiled::Tilemap* LoadTiledMap(std::string filename);
    unsigned int ParseIntFromString(std::string aseprite_key_name);
    sol::state& LoadLuaTableIntoGlobalState(const char *file_name, const char *table_name);
    sol::state* LoadLuaTableIntoTempState(const char *file_name, const char *table_name);
    sol::state* LoadLuaTableIntoTempState(const char *file_name, const char *table_name, sol::state* state_to_load_to);
    Tiled::TileLayer* LoadTileLayer(sol::table& table, int layer_depth);
    void DropLuaTable(const char* table_name);
    extern sol::state lua_global_state;
}