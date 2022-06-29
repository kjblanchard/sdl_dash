#pragma once
#include <supergoon_engine_export.h>
#include <vector>
#include <supergoon_engine/primitives/rectangle.hpp>


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
    static int GetTsxTileNumberFromTileGid(Tsx* tsx, int gid);
    static Point GetTileLocationFromTileDataI(Tilemap* tilemap, int i, bool collection_of_images);
    static Rectangle GetTileSrcRectFromTileDataI(Tilemap* tsx, int i, bool collection_of_images);

    static Point GetTileSourceLocationFromTsxTileNumber(Tsx* tsx, int tsx_tile_number);
    static Rectangle GetTileRectangleFromTsxTileNumber(Tsx* tsx, int tsx_tile_number);
};

