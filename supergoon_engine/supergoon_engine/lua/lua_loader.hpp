#pragma once
#include <external/sol2/forward.hpp>

namespace Lua
{
    sol::state& LoadLuaTableIntoGlobalState(const char *file_name, const char *table_name);
    sol::state* LoadLuaTableIntoTempState(const char *file_name, const char *table_name);
    void DropLuaTable(const char* table_name);
    extern sol::state lua_global_state;
}