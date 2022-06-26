#include <supergoon_engine/tiled/tiled.hpp>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <supergoon_engine/tiled/layer_group.hpp>
#include <supergoon_engine/tiled/tile_layer.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <iostream>

std::vector<Tile *> Tiled::LoadTilesFromTilemap(Tilemap *tilemap)
{
    std::vector<Tile *> tiles;
    for (auto &&layer_group : tilemap->layer_groups)
    {
        for (auto &&layer : layer_group->tile_layers)
        {
            for (auto &&tile : layer->tiles)
            {
                // Do something when you get to the tile.
            }
        }
    }
    return tiles;
}
void Tiled::LoadTexturesFromTilemap(Tilemap *tilemap, Content* content)
{
    for (auto &&tsx : tilemap->tsx_in_tilemap)
    {
        content->LoadTexture(tsx->image_source.c_str());
    }
}