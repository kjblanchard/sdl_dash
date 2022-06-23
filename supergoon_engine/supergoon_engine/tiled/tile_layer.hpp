#pragma once
#include <string>
#include <vector>

class TileLayer
{
private:
    /* data */
public:
    TileLayer(/* args */);
    ~TileLayer();

    int layer_id;
    std::string layer_name;
    int width;
    int height;
    std::vector<int> tiles;
};

TileLayer::TileLayer(/* args */)
{
}

TileLayer::~TileLayer()
{
}
