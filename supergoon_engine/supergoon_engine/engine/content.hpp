#pragma once
#include <supergoon_engine_export.h>

struct SDL_Renderer;
struct SDL_Texture;

class SUPERGOON_ENGINE_EXPORT Content
{
private:
    SDL_Renderer *renderer;
    /* data */
public:
    Content(SDL_Renderer *render);
    SDL_Texture *LoadTexture(const char *filename);
    ~Content();
};
