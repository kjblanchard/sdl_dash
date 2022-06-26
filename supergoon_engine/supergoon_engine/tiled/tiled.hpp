#pragma once
#include <supergoon_engine_export.h>
#include <vector>


class Tile;
class Tilemap;
class Content;

class Tiled
{
private:
    /* data */
public:
    Tiled(/* args */) = delete;
    ~Tiled() = delete;
    static std::vector<Tile*> LoadTilesFromTilemap(Tilemap* tilemap);
    static void LoadTexturesFromTilemap(Tilemap* tilemap, Content* content);
};

