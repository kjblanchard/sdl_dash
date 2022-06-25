#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <supergoon_engine_export.h>
#include <supergoon_engine/tiled/tile_layer.hpp>

// class SUPERGOON_ENGINE_EXPORT LayerGroup
class LayerGroup
{
private:
    /* data */
public:
    LayerGroup(/* args */);
    ~LayerGroup();
    std::vector<std::unique_ptr<TileLayer>> tile_layers;
    std::string name;
};

LayerGroup::LayerGroup(/* args */)
{
}

LayerGroup::~LayerGroup()
{
    //TODO remove this, just for debugging destroying.
    std::cout << "Layer group destroyed" << std::endl;
    tile_layers.clear();
}
