#pragma once
#include <supergoon_engine_export.h>
#include <vector>
#include <supergoon_engine/primitives/rectangle.hpp>

class Tile;

namespace Tiled
{
    class Tilemap;
    class Content;
    class Tsx;

    /**
     * Returns a vector with all of the tiles from this tilemap.
     *
     * @param tilemap The loaded tilemap
     * @return Vector of tiles that can be used to draw with.
     */
    std::vector<Tile *> LoadTilesFromTilemap(Tilemap *tilemap);
    /**
     * Gets the current tsx that the tile gid uses.  Useful to know the source image location
     *
     * @param tilemap The loaded tilemap
     * @param gid The actual id from tiled
     * @return Pointer to a loaded tsx
     */
    Tsx *GetTsxFromGid(Tilemap *tilemap, int gid);
    /**
     * Gets a tsx tile number from the tiled gid.  Useful for knowing where the image is located within a tsx
     *
     * @param tsx The loaded tsx
     * @param gid The actual id from tiled
     * @return The number tile in the spritesheet.
     */
    int GetTsxTileNumberFromTileGid(Tsx *tsx, int gid);
    Point GetTileDstLocationFromTileDataI(Tilemap *tilemap, Tsx *tsx, int i);
    Rectangle GetTileSrcRectFromTileDataI(Tilemap *tilemap, Tsx *tsx, int i);
    Point GetTileSourceLocationFromTsxTileNumber(Tsx *tsx, int tsx_tile_number);
    Rectangle GetTileRectangleFromTsxTileNumber(Tsx *tsx, int tsx_tile_number);

}
