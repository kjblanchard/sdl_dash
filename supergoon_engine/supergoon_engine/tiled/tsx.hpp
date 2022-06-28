#pragma once
#include <supergoon_engine_export.h>
#include <string>


class Tile;
class Tilemap;

class Tsx
{
public:

    std::string layer_name;
    std::string image_source;
    int tile_width;
    int tile_height;
    int first_gid;
};