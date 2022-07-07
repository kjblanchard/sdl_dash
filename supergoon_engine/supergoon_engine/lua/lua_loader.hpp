#pragma once
#include <external/sol2/forward.hpp>
#include <string>

namespace Tiled{
    class Tilemap;
}

namespace Lua
{
    Tiled::Tilemap* LoadTiledMap(std::string filename);
    sol::state& LoadLuaTableIntoGlobalState(const char *file_name, const char *table_name);
    sol::state* LoadLuaTableIntoTempState(const char *file_name, const char *table_name);
    sol::state* LoadLuaTableIntoTempState(const char *file_name, const char *table_name, sol::state* state_to_load_to);
    void DropLuaTable(const char* table_name);
    extern sol::state lua_global_state;
}