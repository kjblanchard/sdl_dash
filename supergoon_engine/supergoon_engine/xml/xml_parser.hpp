#pragma once

#include <supergoon_engine/xml/tinyxml2.h>
#include <string.h>
#include <iostream>
class Tilemap;
class xml_parser
{
private:
public:
    static Tilemap* LoadTiledMap(std::string filename);
};

