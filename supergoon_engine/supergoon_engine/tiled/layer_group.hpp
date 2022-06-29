#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <supergoon_engine_export.h>
#include <supergoon_engine/tiled/tile_layer.hpp>

namespace Tiled
{
    class SUPERGOON_ENGINE_EXPORT LayerGroup
    {
    private:
        /* data */
    public:
        std::vector<std::unique_ptr<TileLayer>> tile_layers;
        std::string name;
    };

}
