#include <supergoon_engine/lua/lua_loader.hpp>
#include <supergoon_engine/lua/lua_helper.hpp>
#include <string.h>
#include <sol2/sol.hpp>
#include <algorithm>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <supergoon_engine/aseprite/aseprite_sheet.hpp>
#include <supergoon_engine/aseprite/aseprite_frame.hpp>
#include <supergoon_engine/aseprite/aseprite_animation.hpp>
#include <supergoon_engine/engine/debug.hpp>
#include <sstream>

sol::state Lua::lua_global_state;
// using namespace Tiled;

void Lua::LoadDataFromAsepriteFile(Aseprite::AsepriteSheet &aseprite_sheet, std::string file)
{
    sol::state temp_state;
    auto thing = sol::this_state(temp_state);
    auto full_path = "./assets/actors/" + file;

    auto char_sprite_sheet = Lua::l_read_json(full_path, thing);
    if (char_sprite_sheet != sol::lua_nil)
    {
        if (char_sprite_sheet.is<sol::table>())
        {
            auto lua_table = char_sprite_sheet.as<sol::lua_table>();
            if (lua_table != sol::lua_nil)
            {
                aseprite_sheet.sprite_sheet_frames = Lua::LoadAsepriteFrames(lua_table);
                aseprite_sheet.sprite_sheet_animations = Lua::LoadAsepriteAnimations(lua_table);
            }
        }
    }
}

std::vector<Aseprite::AsepriteFrame> Lua::LoadAsepriteFrames(sol::table &lua_table)
{
    std::vector<Aseprite::AsepriteFrame> aseprite_frames;
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
            Vector2(frame_rect["x"], frame_rect["y"]),
            Point(frame_rect["w"], frame_rect["h"]));
        aseprite_frames.push_back(frame);
    }
    std::sort(aseprite_frames.begin(), aseprite_frames.end());
    return aseprite_frames;
}

std::vector<Aseprite::AsepriteAnimation> Lua::LoadAsepriteAnimations(sol::table &lua_table)
{
    std::vector<Aseprite::AsepriteAnimation> aseprite_animations;
    sol::table meta_table = lua_table["meta"];
    if (meta_table != sol::lua_nil)
    {
        sol::table frame_tabs = meta_table["frameTags"];
        if (frame_tabs != sol::lua_nil)
        {
            for (auto &i : frame_tabs)
            {
                Aseprite::AsepriteAnimation animation;
                sol::table thing2 = i.second;
                animation.frame_begin = thing2["from"];
                animation.frame_end = thing2["to"];
                animation.name = thing2["name"];
                aseprite_animations.push_back(animation);
            }
        }
    }
    return aseprite_animations;
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

Tiled::Tilemap *Lua::LoadTiledMap(std::string filename)
{
    auto full_name = "./assets/tiled/" + filename + ".lua";
    // Create a unique ptr of the loaded lua state, so it will be removed after reading.
    auto current_doc_lua_state = std::unique_ptr<sol::state>(Lua::LoadLuaTableIntoTempState(full_name.c_str(), "tilemap"));
    // If the Lua state ptr is not null
    if (current_doc_lua_state.get())
    {
        auto tile_map_ptr = new Tiled::Tilemap();
        auto root_element = (*current_doc_lua_state.get())["tilemap"];
        tile_map_ptr->width = root_element["width"];
        tile_map_ptr->height = root_element["height"];
        tile_map_ptr->tile_width = root_element["tilewidth"];
        tile_map_ptr->tile_height = root_element["tileheight"];

        // Get the layers group, and loop through them.
        sol::lua_table layers = root_element["layers"];
        int iLayer = 1, layer_depth = 1;
        while (true)
        {
            // We don't know how big the table is in lua, so test to see if the layer exists, if not, break from the while loop.
            sol::optional<sol::lua_table> hasLayers = layers[iLayer];
            if (hasLayers == sol::nullopt)
                break;
            // Check to see if this is a layer group.
            sol::table layer_group_lua_ref = layers[iLayer];
            std::string layer_name = layer_group_lua_ref["type"];
            if (layer_name == "group")
            {
                auto layer_group_ptr = new Tiled::LayerGroup();
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
                    layer_group_ptr->tile_layers.push_back(std::shared_ptr<Tiled::TileLayer>(LoadTileLayer(tab, layer_depth)));
                    ++j_layer;
                    ++layer_depth;
                }
                tile_map_ptr->layer_groups.push_back(std::shared_ptr<Tiled::LayerGroup>(layer_group_ptr));
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
                    actor_params.type = actor.get<std::string>("type");

                    actor_params.size.x = actor.get<float>("width");
                    actor_params.size.y = actor.get<float>("height");
                    actor_params.layer = layer_depth;

                    sol::lua_table actor_properties = actor["properties"];
                    // Get all properties (string and number) and put in the map
                    actor_properties.for_each([&actor_params](std::pair<sol::object, sol::object> key_value_pair)
                                              {
                        sol::type type = key_value_pair.second.get_type();
                        std::string key = key_value_pair.first.as<std::string>();
                        if(type == sol::type::string)
                        Debug::LogWarn("The type is %d", type);

                        switch (type)
                        {
                        case sol::type::number:
                        {
                            int value = key_value_pair.second.as<int>();
                            actor_params.actor_props.insert({key, value});
                            /* code */
                            break;
                        }
                        case sol::type::table: {
                            auto prop_table = key_value_pair.second.as<sol::lua_table>();
                            prop_table.for_each([&key, &actor_params](std::pair<sol::object, sol::object> prop_key_value_pair){
                                auto prop_key = prop_key_value_pair.first.as<std::string>();
                                auto prop_name = key + prop_key;
                                auto second_type = prop_key_value_pair.second.get_type();
                                if(second_type == sol::type::number)
                                {
                                    if(prop_key_value_pair.second.is<int>())
                                    {
                                        auto value = prop_key_value_pair.second.as<int>();
                                        actor_params.actor_props.insert({prop_name, value});
                                    }
                                    else{
                                        auto value = prop_key_value_pair.second.as<float>();
                                        int value_int = static_cast<int>(value);
                                        actor_params.actor_props.insert({prop_name, value_int});

                                    }
                                }
                                else if (second_type == sol::type::string)
                                {
                                    auto value = prop_key_value_pair.second.as<std::string>();
                                    actor_params.actor_string_props.insert({prop_name, value});
                                }

                            });

                            break;
                        }
                        case sol::type::string: {
                            auto value = key_value_pair.second.as<std::string>();
                            actor_params.actor_string_props.insert({key, value});
                            break;

                        }

                        default:
                            break;
                        } });

                    if (actor_properties["BoxRect"] != sol::lua_nil)
                    {
                        auto rect_table = actor_properties.get<sol::table>("BoxRect");
                        actor_params.box_rect = Rectangle(
                            Vector2(rect_table.get<float>("x"), rect_table.get<float>("y")),
                            Point(rect_table.get<int>("w"), rect_table.get<int>("h")));
                    }
                    else
                    {
                        int width = actor_params.size.x;
                        int height = actor_params.size.y;
                        actor_params.box_rect = Rectangle(
                            Vector2(0, 0),
                            Point(width, height));
                    }
                    tile_map_ptr->actors.push_back(actor_params);
                }
                ++layer_depth;
            }
            ++iLayer;
        }
        sol::lua_table tilesets = root_element["tilesets"];
        for (size_t i = 1; i < tilesets.size() + 1; i++)
        {
            sol::lua_table current_tileset_lua = tilesets[i];
            std::string tsx_tiled_name = current_tileset_lua["name"];
            if (tsx_tiled_name == "actors")
                continue;
            auto tsx = new Tiled::Tsx();
            std::string tsx_name = current_tileset_lua["filename"];
            tsx->first_gid = current_tileset_lua["firstgid"];
            std::stringstream test(tsx_name);
            std::string segment;
            std::vector<std::string> seglist;

            while (std::getline(test, segment, '/'))
            {
                seglist.push_back(segment);
            }
            std::string filename_no_path = seglist.back();
            std::string filename_no_prefix = filename_no_path.erase(filename_no_path.length() - 3);
            std::string filename_lua_prefix = filename_no_prefix + "lua";
            auto tsx_full_name = "./assets/tiled/tilesets/" + filename_lua_prefix;
            Lua::LoadLuaTableIntoTempState(tsx_full_name.c_str(), tsx_name.c_str(), current_doc_lua_state.get());
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
            tile_map_ptr->tsx_in_tilemap.push_back(std::shared_ptr<Tiled::Tsx>(tsx));
        }
        auto guy = tile_map_ptr->tsx_in_tilemap;
        // std::sort(tile_map_ptr->tsx_in_tilemap.begin(), tile_map_ptr->tsx_in_tilemap.end());
        std::sort(tile_map_ptr->tsx_in_tilemap.begin(), tile_map_ptr->tsx_in_tilemap.end(), [](auto &lhs, auto &rhs)
                  { return lhs.get()->first_gid < rhs.get()->first_gid; });
        auto girl = tile_map_ptr->tsx_in_tilemap;
        return tile_map_ptr;
    }
    return nullptr;
}
Tiled::TileLayer *Lua::LoadTileLayer(sol::table &table, int layer_depth)
{
    auto layer_ptr = new Tiled::TileLayer();
    layer_ptr->layer_name = table["name"];
    // layer_ptr->layer_id = table["id"];
    layer_ptr->layer_id = layer_depth;
    layer_ptr->height = table["height"];
    layer_ptr->width = table["width"];
    sol::table layer_tile_data_lua = table["data"];
    for (size_t k_layer = 1; k_layer < layer_tile_data_lua.size() + 1; k_layer++)
    {
        layer_ptr->tiles.push_back(layer_tile_data_lua[k_layer]);
    }
    return layer_ptr;
}
