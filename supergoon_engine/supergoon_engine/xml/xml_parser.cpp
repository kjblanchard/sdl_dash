#include <supergoon_engine/xml/xml_parser.hpp>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <stdexcept>

Tilemap *xml_parser::LoadTiledMap(std::string filename)
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
        bool still_reading = true;
        while (still_reading)
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
                still_reading = false;
            else
                element = element->NextSiblingElement("layer");
            // Add this layer to the tile layers so that it is deleted properly.
            layer_group_ptr->tile_layers.push_back(std::unique_ptr<TileLayer>(layer_ptr));
        }
        tile_map_ptr->layer_groups.push_back(std::unique_ptr<LayerGroup>(layer_group_ptr));

        return tile_map_ptr;
    }
    return nullptr;
}