#include <supergoon_engine/xml/xml_parser.hpp>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <stdexcept>

tinyxml2::XMLDocument *xml_parser::LoadTiledMap(std::string filename)
{
    auto full_name = "./assets/tiled/" + filename + ".tmx";
    auto current_doc = new tinyxml2::XMLDocument();
    auto result = current_doc->LoadFile(full_name.c_str());
    if (result != tinyxml2::XMLError::XML_SUCCESS)
        return current_doc;
    auto root_element = current_doc->RootElement();
    if (root_element)
    {
        // Get the maps attributes.
        auto map_version = root_element->Attribute("version");
        auto map_width = root_element->IntAttribute("width");
        auto map_height = root_element->IntAttribute("height");
        auto tile_width = root_element->IntAttribute("tilewidth");
        auto tile_height = root_element->IntAttribute("tileheight");

        // start to get the map elements.
        auto first_group = root_element->FirstChildElement("group");
        auto first_group_name = first_group->Attribute("name");

        // go through each layer until we are at the end
        auto element = first_group->FirstChildElement("layer");
        auto last_element = first_group->LastChildElement("layer");
        bool still_reading = true;
        while (still_reading)
        {
            auto layer_name = element->Attribute("name");
            std::cout << layer_name << "Is the layer name that we see now\n" << std::endl;
            auto tile_data = element->FirstChildElement("data");
            auto tile_data_string = tile_data->GetText();
            auto tile_data_size = strlen(tile_data_string);

            // Loop through the string and get the tile numbers, separated by commas.
            auto delim = ',';
            std::string current_num = "";
            std::vector<int> tiles;

            for (size_t i = 0; i < tile_data_size; i++)
            {
                auto current_char = tile_data_string[i];

                // word separator
                if (current_char == delim)
                {
                    auto current_number = stoi(current_num);
                    tiles.push_back(current_number);
                    current_num = "";
                    continue;
                }
                // If this isn't a number or a delim, continue
                if (!isdigit(current_char))
                    continue;
                current_num += current_char;
                // cout << "The tile number is " << tile_data_string[i] << endl;
            }

            for (size_t i = 0; i < tiles.size(); i++)
            {
                std::cout << "The tile number is: " << tiles[i] << std::endl;
            }

            if (element == last_element)
                still_reading = false;
            else
                element = element->NextSiblingElement("layer");
        }
    }
    throw std::runtime_error("Hello");
    return current_doc;
}