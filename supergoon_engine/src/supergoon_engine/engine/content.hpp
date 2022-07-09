#pragma once
#include <supergoon_engine_export.h>
#include <map>
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

enum class LoadType
{
    Default = 0,
    Tile = 1,
    Aseprite = 2,

};

class SUPERGOON_ENGINE_EXPORT Content
{
private:
    SDL_Renderer *renderer;
    std::map<std::string, SDL_Texture *> loaded_textures;

public:
    Content(SDL_Renderer *render);
    SDL_Texture *LoadTexture(const char *filename, LoadType load_type);
    ~Content();
};
