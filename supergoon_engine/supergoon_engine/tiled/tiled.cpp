#include <supergoon_engine/tiled/tiled.hpp>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <supergoon_engine/tiled/layer_group.hpp>
#include <supergoon_engine/tiled/tile_layer.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/tiled/tsx.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>

std::vector<Tile *> Tiled::LoadTilesFromTilemap(Tilemap *tilemap)
{
    std::vector<Tile *> tiles;
    for (size_t layer_group_i = 0; layer_group_i < tilemap->layer_groups.size(); layer_group_i++)
    {
        auto &layer_group = tilemap->layer_groups[layer_group_i];
        for (size_t layer_i = 0; layer_i < layer_group->tile_layers.size(); layer_i++)
        {
            auto &layer = layer_group->tile_layers[layer_i];

            for (size_t tile_i = 0; tile_i < layer->tiles.size(); tile_i++)
            {
                auto tile_gid = layer->tiles[tile_i];
                // If gid is 0, skip as this is a blank tile.
                if (tile_gid == 0)
                    continue;
                auto tsx = Tiled::GetTsxFromGid(tilemap, tile_gid);
                auto dst_rect = GetTileSrcRectFromTileDataI(tilemap, tsx, static_cast<int>(tile_i));
                auto tsx_tile_num = GetTsxTileNumberFromTileGid(tsx, tile_gid);
                Rectangle source_rect = GetTileRectangleFromTsxTileNumber(tsx, tsx_tile_num);

                auto new_tile = new Tile(dst_rect.location.ToVector2(), tsx->image_source.c_str(), source_rect);
                tiles.push_back(new_tile);
            }
        }
    }
    return tiles;
}

Tsx *Tiled::GetTsxFromGid(Tilemap *tilemap, int gid)
{
    for (size_t i = 0; i < tilemap->tsx_in_tilemap.size(); i++)
    {
        auto &tsx = tilemap->tsx_in_tilemap[i];
        // If we are the last tsx, return this tsx
        if (i == tilemap->tsx_in_tilemap.size() - 1)
            return tsx.get();
        // Else, check to see if the gid is in this one, but less than the next's first gid
        if (gid >= tsx->first_gid && gid < tilemap->tsx_in_tilemap[i + 1]->first_gid)
            return tsx.get();
    }
    return nullptr;
}

int Tiled::GetTsxTileNumberFromTileGid(Tsx *tsx, int gid)
{
    return gid - tsx->first_gid;
}

Point Tiled::GetTileDstLocationFromTileDataI(Tilemap *tilemap, Tsx *tsx, int i)
{

    int x = (i % tilemap->width) * tilemap->tile_width;
    int y = (i / tilemap->width) * tilemap->tile_height;
    // Collection of images needs an offset due to the way tiled draws them in the editor.
    if (tsx->collection_of_images)
    {
        auto offset = tsx->tile_height - tilemap->tile_height;
        y -= offset;
    }
    return Point(x, y);
}
Rectangle Tiled::GetTileSrcRectFromTileDataI(Tilemap *tilemap, Tsx *tsx, int i)
{
    return Rectangle(
        Tiled::GetTileDstLocationFromTileDataI(tilemap, tsx, i),
        Point(tilemap->tile_width, tilemap->tile_height));
}
Rectangle Tiled::GetTileRectangleFromTsxTileNumber(Tsx *tsx, int tsx_tile_number)
{
    return Rectangle(
        Tiled::GetTileSourceLocationFromTsxTileNumber(tsx, tsx_tile_number),
        Point(tsx->tile_width, tsx->tile_height));
}
Point Tiled::GetTileSourceLocationFromTsxTileNumber(Tsx *tsx, int tsx_tile_number)
{
    int x = (tsx_tile_number % tsx->columns) * tsx->tile_width;
    int y = (tsx_tile_number / tsx->columns) * tsx->tile_height;
    return Point(x, y);
}
