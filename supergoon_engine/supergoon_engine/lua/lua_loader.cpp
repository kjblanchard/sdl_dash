#include <supergoon_engine/lua/lua_loader.hpp>
#include <string.h>

sol::state Lua::lua_global_state;

sol::lua_table Lua::LoadLuaTableIntoGlobalState(const char *file_name, const char *table_name)
{

    // Test if the script is valid
    sol::load_result script = lua_global_state.load_file(file_name);
    if (!script.valid())
    {
        sol::error err = script;
        auto error_message = err.what();
        printf("Error loading the lua script: %s", error_message);
        return nullptr;
    }
    lua_global_state[table_name] = lua_global_state.script_file(file_name);

    return lua_global_state[table_name];
}
sol::state Lua::LoadLuaTableIntoTempState(const char *file_name, const char *table_name)
{
    sol::state temp_state;
    // Test if the script is valid
    sol::load_result script = temp_state.load_file(file_name);
    if (!script.valid())
    {
        sol::error err = script;
        auto error_message = err.what();
        printf("Error loading the lua script: %s", error_message);
        return nullptr;
    }
        temp_state[table_name] = temp_state.script_file(file_name);

    return temp_state;
}
