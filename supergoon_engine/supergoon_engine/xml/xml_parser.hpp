#pragma once

#include <supergoon_engine/xml/tinyxml2.h>
#include <string.h>
#include <iostream>
class xml_parser
{
private:
public:
    static tinyxml2::XMLDocument* LoadTiledMap(std::string filename);
};

