#pragma once
#include <memory>
#include <vector>
#include <supergoon_engine/tiled/tileset_info.hpp>
#include <supergoon_engine_export.h>
#include <supergoon_engine/tiled/layer_group.hpp>
#include <supergoon_engine/tiled/tsx.hpp>

namespace Tiled
{
    class SUPERGOON_ENGINE_EXPORT Tilemap
    {
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

        std::vector<std::shared_ptr<TilesetInfo>> tileset_infos;
        std::vector<std::shared_ptr<Tiled::LayerGroup>> layer_groups;
        std::vector<std::shared_ptr<Tsx>> tsx_in_tilemap;
    };

}
