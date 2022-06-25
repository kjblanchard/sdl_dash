#pragma once
#include <memory>
#include <vector>
#include <supergoon_engine/tiled/tileset_info.hpp>
#include <supergoon_engine_export.h>
#include <supergoon_engine/tiled/layer_group.hpp>

// class SUPERGOON_ENGINE_EXPORT Tilemap
class Tilemap
{
private:
    /* data */
public:
    inline ~Tilemap()
    {
        tileset_infos.clear();
        layer_groups.clear();
    }
    int width;
    int height;
    int tile_width;
    int tile_height;

    std::vector<std::unique_ptr<TilesetInfo>> tileset_infos;
    std::vector<std::unique_ptr<LayerGroup>> layer_groups;
};

