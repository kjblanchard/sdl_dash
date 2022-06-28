#pragma once
#include <supergoon_engine_export.h>
#include <vector>


class Tile;
class Tilemap;
class Content;
class Tsx;

class Tiled
{
private:
    /* data */
public:
    Tiled(/* args */) = delete;
    ~Tiled() = delete;
    static std::vector<Tile*> LoadTilesFromTilemap(Tilemap* tilemap);
    static Tsx* GetTsxFromGid(Tilemap* tilemap, int gid);
    static void LoadTexturesFromTilemap(Tilemap* tilemap, Content* content);
    static int GetTileNumberFromTileGid(Tilemap* tilemap, int gid);
    static int GetTileXValueFromTileDataI(Tilemap* tilemap, int i);
};

