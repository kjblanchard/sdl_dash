#include <supergoon_engine/tiled/tiled.hpp>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <supergoon_engine/tiled/layer_group.hpp>
#include <supergoon_engine/tiled/tile_layer.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <supergoon_engine/tiled/tsx.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>
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
                // If gid is 0, skip as this is a blank tile.
                if (tile == 0)
                    continue;
                auto tsx = Tiled::GetTsxFromGid(tilemap, tile);
                std::cout << "The image source for this tile is " << tsx->image_source << std::endl;

                Vector2 tile_location;
                Rectangle source_rect;

                auto new_tile = new Tile(tile_location, tsx->image_source.c_str(), source_rect);
                tiles.push_back(new_tile);
            }
        }
    }
    return tiles;
}
void Tiled::LoadTexturesFromTilemap(Tilemap *tilemap, Content *content)
{
    for (auto &&tsx : tilemap->tsx_in_tilemap)
    {
        content->LoadTexture(tsx->image_source.c_str());
    }
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
int Tiled::GetTileNumberFromTileGid(Tilemap *tilemap, int gid)
{
}

int Tiled::GetTileXValueFromTileDataI(Tilemap *tilemap, int i)
{
}