#include <supergoon_engine/engine/content.hpp>
#include <SDL_surface.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

Content::Content(SDL_Renderer *render)
{
    renderer = render;
}

Content::~Content()
{
}
SDL_Texture *Content::LoadTexture(const char *filename)
{
    // TODO handle the location and postfix better, since we can only load tilesets currently.
    // Check to see if we have already loaded it.
    std::cout << "Texture to look for is " << filename << std::endl;
    if (loaded_textures.contains(filename))
        return loaded_textures.find(filename)->second;
    SDL_Surface *
        surf = NULL;
    SDL_Texture *tex = NULL;
    std::string prefix = "./assets/tiled/tilesets/";
    std::string full = prefix + filename;
    std::cout << "Full path is " << full << std::endl;

    surf = IMG_Load(full.c_str());
    if (surf == NULL)
    {
        std::cout << "Error loading: " << IMG_GetError() << std::endl;
    }
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    if (tex == NULL)
    {
        std::cout << "Error loading: " << IMG_GetError() << std::endl;
    }
    SDL_FreeSurface(surf);
    loaded_textures.emplace(filename, tex);
    return tex;
}