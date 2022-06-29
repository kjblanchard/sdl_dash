#pragma once
#include <supergoon_engine_export.h>
#include <vector>
#include <supergoon_engine/primitives/rectangle.hpp>

class Tile;
class Tilemap;
class Content;
class Tsx;

/**
* This class has a lot of useful functions for working with loaded TSX and TMX data
* This class just has halper functions, and cannot be instantiated.
*/
class TiledLoader
{
private:
    TiledLoader() = delete;
    ~TiledLoader() = delete;

public:
    /**
     * Returns a vector with all of the tiles from this tilemap.
     *
     * @param tilemap The loaded tilemap
     * @return Vector of tiles that can be used to draw with.
     */
    static std::vector<Tile *> LoadTilesFromTilemap(Tilemap *tilemap);
    /**
     * Gets the current tsx that the tile gid uses.  Useful to know the source image location
     *
     * @param tilemap The loaded tilemap
     * @param gid The actual id from tiled
     * @return Pointer to a loaded tsx
     */
    static Tsx *GetTsxFromGid(Tilemap *tilemap, int gid);
    /**
     * Gets a tsx tile number from the tiled gid.  Useful for knowing where the image is located within a tsx
     *
     * @param tsx The loaded tsx
     * @param gid The actual id from tiled
     * @return The number tile in the spritesheet.
     */
    static int GetTsxTileNumberFromTileGid(Tsx *tsx, int gid);
    static Point GetTileDstLocationFromTileDataI(Tilemap *tilemap, Tsx *tsx, int i);
    static Rectangle GetTileSrcRectFromTileDataI(Tilemap *tilemap, Tsx *tsx, int i);
    static Point GetTileSourceLocationFromTsxTileNumber(Tsx *tsx, int tsx_tile_number);
    static Rectangle GetTileRectangleFromTsxTileNumber(Tsx *tsx, int tsx_tile_number);
};
