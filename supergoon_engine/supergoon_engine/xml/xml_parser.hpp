#pragma once

#include <supergoon_engine_export.h>
#include <supergoon_engine/xml/tinyxml2.h>
#include <string.h>
#include <iostream>
class Tilemap;
class SUPERGOON_ENGINE_EXPORT xml_parser
{
private:
public:
    static Tilemap* LoadTiledMap(std::string filename);
};

