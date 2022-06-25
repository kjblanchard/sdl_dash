#pragma once
#include <string>
#include <vector>
#include <supergoon_engine_export.h>

class SUPERGOON_ENGINE_EXPORT TileLayer
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

