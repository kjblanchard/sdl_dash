#include <supergoon_engine/lua/lua_loader.hpp>
#include <string.h>
#include <external/sol2/sol.hpp>
#include <supergoon_engine/tiled/tilemap.hpp>

sol::state Lua::lua_global_state;
using namespace Tiled;

sol::state &Lua::LoadLuaTableIntoGlobalState(const char *file_name, const char *table_name)
{

    // Test if the script is valid
    sol::load_result script = lua_global_state.load_file(file_name);
    if (!script.valid())
    {
        sol::error err = script;
        auto error_message = err.what();
        std::cout << "Error loading the lua script: " << error_message << std::endl;
    }
    lua_global_state[table_name] = lua_global_state.script_file(file_name);
    return Lua::lua_global_state;
}
sol::state *Lua::LoadLuaTableIntoTempState(const char *file_name, const char *table_name)
{
    sol::state *temp_state = new sol::state();
    Lua::LoadLuaTableIntoTempState(file_name, table_name, temp_state);

    return temp_state;
}
sol::state *Lua::LoadLuaTableIntoTempState(const char *file_name, const char *table_name, sol::state *state_to_load_to)
{
    sol::load_result script = state_to_load_to->load_file(file_name);
    if (!script.valid())
    {
        sol::error err = script;
        auto error_message = err.what();
        std::cout << "Error loading the lua script: " << error_message << std::endl;
        return nullptr;
    }
    (*state_to_load_to)[table_name] = state_to_load_to->script_file(file_name);
    return state_to_load_to;
}

Tilemap *Lua::LoadTiledMap(std::string filename)
{
    auto full_name = "./assets/tiled/" + filename + ".lua";
    // Create a unique ptr of the loaded lua state, so it will be removed after reading.
    auto current_doc_lua_state = std::unique_ptr<sol::state>(Lua::LoadLuaTableIntoTempState(full_name.c_str(), "tilemap"));
    // If the Lua state ptr is not null
    if (current_doc_lua_state.get())
    {
        auto tile_map_ptr = new Tilemap();
        auto root_element = (*current_doc_lua_state.get())["tilemap"];
        tile_map_ptr->width = root_element["width"];
        tile_map_ptr->height = root_element["height"];
        tile_map_ptr->tile_width = root_element["tilewidth"];
        tile_map_ptr->tile_height = root_element["tileheight"];

        // Get the layers group, and loop through them.
        sol::lua_table layers = root_element["layers"];
        int iLayer = 1;
        while (true)
        {
            // We don't know how big the table is in lua, so test to see if the layer exists, if not, break from the while loop.
            sol::optional<sol::lua_table> hasLayer = layers[iLayer];
            if (hasLayer == sol::nullopt)
                break;
            // Check to see if this is a layer group.
            sol::table layer_group_lua_ref = layers[iLayer];
            std::string layer_name = layer_group_lua_ref["type"];
            if (layer_name == "group")
            {
                auto layer_group_ptr = new LayerGroup();
                // Go through each layer in the group
                layer_group_ptr->name = layer_group_lua_ref["name"];
                sol::table layer_group_layers_lua = layer_group_lua_ref["layers"];
                int j_layer = 1;
                while (true)
                {
                    sol::optional<sol::lua_table> hasLayer = layer_group_layers_lua[j_layer];
                    if (hasLayer == sol::nullopt)
                        break;
                    auto layer_ptr = new TileLayer();
                    layer_ptr->layer_name = layer_group_layers_lua[j_layer]["name"];
                    layer_ptr->layer_id = layer_group_layers_lua[j_layer]["id"];
                    layer_ptr->height = layer_group_layers_lua[j_layer]["height"];
                    layer_ptr->width = layer_group_layers_lua[j_layer]["width"];
                    sol::table layer_tile_data_lua = layer_group_layers_lua[j_layer]["data"];
                    // int k_layer = 1;
                    for (size_t k_layer = 1; k_layer < layer_tile_data_lua.size() + 1; k_layer++)
                    {
                        // hasLayer = layer_tile_data_lua[k_layer];
                        // if (hasLayer == sol::nullopt)
                        //     break;
                        layer_ptr->tiles.push_back(layer_tile_data_lua[k_layer]);
                    }
                    layer_group_ptr->tile_layers.push_back(std::shared_ptr<TileLayer>(layer_ptr));
                    ++j_layer;
                }
                tile_map_ptr->layer_groups.push_back(std::shared_ptr<LayerGroup>(layer_group_ptr));
            }
            // TODO load layers not in a group or object layer
            else if (layer_name == "objectgroup")
            {
                sol::lua_table object_group_lua = layers[iLayer];
                sol::lua_table objects_lua = object_group_lua["objects"];
                for (size_t j = 1; j < objects_lua.size() + 1; j++)
                {
                    sol::lua_table actor = objects_lua[j];
                    auto actor_params = Objects::ActorParams();
                    std::string actor_name = actor["name"];
                    actor_params.actor_name = actor_name;
                    actor_params.loc.x = actor["x"];
                    actor_params.loc.y = actor["y"];
                    tile_map_ptr->actors.push_back(actor_params);
                }
            }
            ++iLayer;
        }
        sol::lua_table tilesets = root_element["tilesets"];
        for (size_t i = 1; i < tilesets.size() + 1; i++)
        {
            auto tsx = new Tsx();
            sol::lua_table current_tileset_lua = tilesets[i];
            tsx->first_gid = current_tileset_lua["firstgid"];
            std::string tsx_name = current_tileset_lua["filename"];
            auto tsx_full_name = "./assets/tiled/tilesets/" + tsx_name;
            Lua::LoadLuaTableIntoTempState(tsx_full_name.c_str(), tsx_name.c_str(), current_doc_lua_state.get());
            // sol::lua_table loaded_tsx_lua = root_element[tsx_name.c_str()];
            sol::lua_table loaded_tsx_lua = (*current_doc_lua_state.get())[tsx_name.c_str()];
            tsx->layer_name = loaded_tsx_lua["name"];
            tsx->tile_height = loaded_tsx_lua["tileheight"];
            tsx->tile_width = loaded_tsx_lua["tilewidth"];
            tsx->columns = loaded_tsx_lua["columns"];
            // Check to see if this is a Image TSX
            sol::lua_table image_tsx_tiles = loaded_tsx_lua["tiles"];
            if (image_tsx_tiles.size() > 0)
            {
                tsx->image_source = image_tsx_tiles[1]["image"];
                tsx->collection_of_images = true;
            }
            else
            {
                tsx->image_source = loaded_tsx_lua["image"];
                tsx->collection_of_images = false;
            }
            tile_map_ptr->tsx_in_tilemap.push_back(std::shared_ptr<Tsx>(tsx));
        }
        return tile_map_ptr;
    }
    return nullptr;
}
