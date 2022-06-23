#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <supergoon_engine/tiled/tile_layer.hpp>

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
