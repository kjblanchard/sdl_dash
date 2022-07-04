#include <supergoon_engine/xml/xml_parser.hpp>
#include <supergoon_engine/xml/tinyxml2.h>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <stdexcept>

using namespace Tiled;

Tilemap *XmlParser::LoadTiledMap(std::string filename)
{
    auto full_name = "./assets/tiled/" + filename + ".tmx";
    auto current_doc = new tinyxml2::XMLDocument();
    auto result = current_doc->LoadFile(full_name.c_str());
    if (result != tinyxml2::XMLError::XML_SUCCESS)
        return nullptr;
    auto root_element = current_doc->RootElement();
    if (root_element)
    {
        // Get the maps attributes.
        auto tile_map_ptr = new Tilemap();

        tile_map_ptr->width = root_element->IntAttribute("width");
        tile_map_ptr->height = root_element->IntAttribute("height");
        tile_map_ptr->tile_width = root_element->IntAttribute("tilewidth");
        tile_map_ptr->tile_height = root_element->IntAttribute("tileheight");

        // start to get the map elements, for now just grab the first group and loop through them.

        auto layer_group_ptr = new LayerGroup();
        auto first_group = root_element->FirstChildElement("group");
        layer_group_ptr->name = first_group->Attribute("name");

        // go through each layer in the group  until we are at the end

        auto element = first_group->FirstChildElement("layer");
        auto last_element = first_group->LastChildElement("layer");
        bool still_reading_layers = true;
        while (still_reading_layers)
        {
            auto layer_ptr = new TileLayer();
            layer_ptr->layer_name = element->Attribute("name");
            layer_ptr->layer_id = element->IntAttribute("id");
            layer_ptr->height = element->IntAttribute("height");
            layer_ptr->width = element->IntAttribute("width");
            // Read the actual tile data in this layer.
            auto tile_data = element->FirstChildElement("data");
            auto tile_data_string = tile_data->GetText();
            auto tile_data_size = strlen(tile_data_string);
            // Loop through the string and get the tile numbers, separated by commas.
            auto delim = ',';
            std::string current_num = "";

            for (size_t i = 0; i < tile_data_size; i++)
            {
                auto current_char = tile_data_string[i];

                // word separator
                if (current_char == delim)
                {
                    auto current_number = stoi(current_num);
                    layer_ptr->tiles.push_back(current_number);
                    current_num = "";
                    continue;
                }
                // If this isn't a number or a delim, continue
                if (!isdigit(current_char))
                    continue;
                current_num += current_char;
            }

            if (element == last_element)
                still_reading_layers = false;
            else
                element = element->NextSiblingElement("layer");
            // Add this layer to the tile layers so that it is deleted properly.
            layer_group_ptr->tile_layers.push_back(std::shared_ptr<TileLayer>(layer_ptr));
        }
        tile_map_ptr->layer_groups.push_back(std::shared_ptr<LayerGroup>(layer_group_ptr));

        // Grab the actor information.
        element = root_element->FirstChildElement("objectgroup");
        auto actor = element->FirstChildElement("object");
        last_element = element->LastChildElement("object");
        still_reading_layers = true;
        while (still_reading_layers)
        {
            auto actor_params = Objects::ActorParams();
            actor_params.actor_name = actor->Attribute("name");
            actor_params.loc.x = actor->FloatAttribute("x");
            actor_params.loc.y = actor->FloatAttribute("y");

            if (actor == last_element)
                still_reading_layers = false;
            else
                actor = actor->NextSiblingElement("object");
            tile_map_ptr->actors.push_back(actor_params);
        }
        // Grab all the tilesets information.

        element = root_element->FirstChildElement("tileset");
        last_element = root_element->LastChildElement("tileset");
        bool still_reading_tilesets = true;
        while (still_reading_tilesets)
        {
            auto tsx = new Tsx();
            tsx->first_gid = element->IntAttribute("firstgid");
            std::string tsx_name = element->Attribute("source");
            auto tsx_full_name = "./assets/tiled/" + tsx_name;
            auto current_tsx = new tinyxml2::XMLDocument();
            auto tsx_result = current_tsx->LoadFile(tsx_full_name.c_str());
            if (tsx_result != tinyxml2::XMLError::XML_SUCCESS)
                continue;
            auto tsx_root_element = current_tsx->RootElement();
            if (tsx_root_element)
            {
                tsx->layer_name = tsx_root_element->Attribute("name");
                tsx->tile_height = tsx_root_element->IntAttribute("tileheight");
                tsx->tile_width = tsx_root_element->IntAttribute("tilewidth");
                tsx->columns = tsx_root_element->IntAttribute("columns");
                // Check to see if this is a Image TSX
                auto is_image_tsx = tsx_root_element->FirstChildElement("tile");
                if (is_image_tsx != nullptr)
                {
                    auto image_element = is_image_tsx->FirstChildElement("image");
                    tsx->image_source = image_element->Attribute("source");
                    tsx->collection_of_images = true;
                }
                else
                {
                    auto image_element = tsx_root_element->FirstChildElement("image");
                    tsx->image_source = image_element->Attribute("source");
                    tsx->collection_of_images = false;
                }
            }
            if (element == last_element)
                still_reading_tilesets = false;
            else
                element = element->NextSiblingElement("tileset");
            tile_map_ptr->tsx_in_tilemap.push_back(std::shared_ptr<Tsx>(tsx));
        }
        return tile_map_ptr;
    }
    return nullptr;
}