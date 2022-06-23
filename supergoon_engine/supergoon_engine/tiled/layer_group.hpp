#pragma once
#include <vector>
#include <memory>
#include <string>

class TileLayer;
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
    tile_layers.clear();
}
