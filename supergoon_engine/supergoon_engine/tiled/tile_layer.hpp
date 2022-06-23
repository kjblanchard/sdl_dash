#pragma once
#include <string>
#include <vector>

class TileLayer
{
private:
    /* data */
public:
    int layer_id;
    std::string layer_name;
    int width;
    int height;
    std::vector<int> tiles;
};

