#pragma once
#include <supergoon_engine_export.h>
#include <string>


namespace Tiled
{

    class Tsx
    {
    public:
        std::string layer_name;
        std::string image_source;
        int tile_width;
        int tile_height;
        int first_gid;
        int columns;
        bool collection_of_images;
    };

}