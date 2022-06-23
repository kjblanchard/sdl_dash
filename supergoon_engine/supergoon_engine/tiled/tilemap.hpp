#pragma once
#include <memory>
#include <vector>

class TilesetInfo;
class LayerGroup;

class Tilemap
{
private:
    /* data */
public:
    Tilemap(/* args */);
    ~Tilemap();
    int width;
    int height;
    int tile_width;
    int tile_height;

    std::vector<std::unique_ptr<TilesetInfo>> tileset_infos;
    std::vector<std::unique_ptr<LayerGroup>> layer_groups;
};

Tilemap::Tilemap(/* args */)
{
}

Tilemap::~Tilemap()
{
    tileset_infos.clear();
    layer_groups.clear();
}
