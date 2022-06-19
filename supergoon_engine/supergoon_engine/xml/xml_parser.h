#include <supergoon_engine/xml/tinyxml2.h>
#include <string.h>
#include <iostream>
class xml_parser
{
private:
public:
    static tinyxml2::XMLDocument LoadTiledMap(std::string filename);
};
tinyxml2::XMLDocument xml_parser::LoadTiledMap(std::string filename)
{
    auto full_name = "./assets/tiled/" + filename;
    tinyxml2::XMLDocument current_doc = new tinyxml2::XMLDocument();
    auto result = current_doc.LoadFile(full_name.c_str());
    if (result != tinyxml2::XMLError::XML_SUCCESS)
        return &current_doc;
    auto him = current_doc.RootElement();
    if (him)
    {
        auto map_version = him->Attribute("version");
        std::cout << "The map version is " << map_version << std::endl;
    }
    return &current_doc;
}
