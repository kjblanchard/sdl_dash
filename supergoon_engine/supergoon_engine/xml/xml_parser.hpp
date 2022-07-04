#pragma once

#include <supergoon_engine_export.h>
#include <string.h>
#include <iostream>
namespace Tiled
{

    class Tilemap;
}
class SUPERGOON_ENGINE_EXPORT XmlParser
{
private:
public:
    static Tiled::Tilemap *LoadTiledMap(std::string filename);
};
