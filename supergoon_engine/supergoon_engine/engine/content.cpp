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
    SDL_Surface *surf;
    SDL_Texture *tex;
    std::string prefix = "./assets/tiled/tilesets/";
    auto full = prefix + filename + ".png";

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
    return tex;
}