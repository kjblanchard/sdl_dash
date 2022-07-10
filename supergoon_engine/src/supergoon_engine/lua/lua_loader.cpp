#include <supergoon_engine/lua/lua_loader.hpp>
#include <supergoon_engine/lua/lua_helper.hpp>
#include <string.h>
#include <sol2/sol.hpp>
#include <algorithm>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <supergoon_engine/aseprite/aseprite_frame.hpp>
#include <sstream>

sol::state Lua::lua_global_state;
using namespace Tiled;

std::vector<Aseprite::AsepriteFrame> Lua::LoadAsepriteFrames(std::string files)
{
    sol::state temp_state;
    auto thing = sol::this_state(temp_state);
    auto full_path = "./assets/actors/" + files;
    std::vector<Aseprite::AsepriteFrame> aseprite_frames;

    auto char_sprite_sheet = Lua::l_read_json(full_path, thing);
    if (char_sprite_sheet != sol::lua_nil)
    {
        if (char_sprite_sheet.is<sol::table>())
        {
            auto lua_table = char_sprite_sheet.as<sol::lua_table>();
            if (lua_table != sol::lua_nil)
            {
                sol::table frames = lua_table["frames"];
                for (const auto &key_value_pair : frames)
                {
                    Aseprite::AsepriteFrame frame;
                    auto key = key_value_pair.first.as<std::string>();
                    frame.frame_num = Lua::ParseIntFromString(key);
                    sol::table value = key_value_pair.second;
                    frame.millisecond_length = value["duration"];
                    sol::table frame_rect = value["frame"];
                    frame.source_rect = Rectangle(
                        Point(frame_rect["x"], frame_rect["y"]),
                        Point(frame_rect["w"], frame_rect["h"]));
                    aseprite_frames.push_back(frame);
                }
                std::sort(aseprite_frames.begin(), aseprite_frames.end());
            }
        }
    }
    return aseprite_frames;
}

unsigned int Lua::ParseIntFromString(std::string aseprite_key_name)
{
    std::stringstream str_strm;
    str_strm << aseprite_key_name; // convert the string s into stringstream
    std::string temp_str;
    unsigned int temp_int;
    while (!str_strm.eof())
    {
        str_strm >> temp_str; // take words into temp_str one by one
        if (std::stringstream(temp_str) >> temp_int)
        { // try to convert string to int
            return temp_int;
        }
        temp_str = ""; // clear temp string
    }
    return 0;
}

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
                    sol::table tab = layer_group_layers_lua[j_layer];
                    layer_group_ptr->tile_layers.push_back(std::shared_ptr<TileLayer>(LoadTileLayer(tab)));
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
        auto guy = tile_map_ptr->tsx_in_tilemap;
        std::sort(tile_map_ptr->tsx_in_tilemap.begin(), tile_map_ptr->tsx_in_tilemap.end());
        auto girl = tile_map_ptr->tsx_in_tilemap;
        return tile_map_ptr;
    }
    return nullptr;
}
Tiled::TileLayer *Lua::LoadTileLayer(sol::table &table)
{
    auto layer_ptr = new TileLayer();
    layer_ptr->layer_name = table["name"];
    layer_ptr->layer_id = table["id"];
    layer_ptr->height = table["height"];
    layer_ptr->width = table["width"];
    sol::table layer_tile_data_lua = table["data"];
    for (size_t k_layer = 1; k_layer < layer_tile_data_lua.size() + 1; k_layer++)
    {
        layer_ptr->tiles.push_back(layer_tile_data_lua[k_layer]);
    }
    return layer_ptr;
}
