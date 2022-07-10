#include <supergoon_engine/engine/content.hpp>
#include <SDL_surface.h>
#include <SDL.h>
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
std::shared_ptr<SDL_Texture> Content::LoadTexture(const char *filename, LoadType load_type)
{
    if (IsAlreadyLoaded(filename))
        return loaded_textures.find(filename)->second.lock();

    SDL_Surface *
        surf = nullptr;
    SDL_Texture *tex = nullptr;
    std::string prefix = "";
    switch (load_type)
    {
    case LoadType::Default:
        std::cerr << "Didn't specify a good load type.  This is used to know the path to load the file from." << std::endl;
        return nullptr;
    case LoadType::Tile:
        prefix = "./assets/tiled/tilesets/";
        break;
    case LoadType::Aseprite:
        prefix = "./assets/actors/";
        break;
    }
    std::string full = prefix + filename;

    surf = IMG_Load(full.c_str());
    if (surf == nullptr)
    {
        std::cout << "Error loading: " << IMG_GetError() << std::endl;
    }
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    if (tex == nullptr)
    {
        std::cout << "Error loading: " << IMG_GetError() << std::endl;
    }
    SDL_FreeSurface(surf);
    // Make a shared ptr that calls destroy texture on deletion.
    auto shared_ptr = std::shared_ptr<SDL_Texture>(
        tex,
        [](SDL_Texture *ptr)
        {
            SDL_DestroyTexture(ptr);
        });
    loaded_textures.emplace(filename, shared_ptr);
    return shared_ptr;
}
bool Content::IsAlreadyLoaded(const char *filename)
{
    if (loaded_textures.contains(filename))
    {
        auto str_tex = loaded_textures.find(filename);
        if (!str_tex->second.expired())
            return true;
        else
            loaded_textures.erase(filename);
    }
    return false;
}