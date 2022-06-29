#pragma once

#include <supergoon_engine_export.h>
#include <supergoon_engine/xml/tinyxml2.h>
#include <string.h>
#include <iostream>
namespace Tiled
{

    class Tilemap;
}
class SUPERGOON_ENGINE_EXPORT xml_parser
{
private:
public:
    static Tiled::Tilemap *LoadTiledMap(std::string filename);
};
