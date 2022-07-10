#pragma once
#include <supergoon_engine_export.h>
#include <memory>
#include <map>
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

/**
 * Load Type is used when loading so that we know the correct prefix to add to the load path.
 *
 */
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
    /**
     * Checks to see if the texture is already loaded and valid.
     *
     * @param filename The file to check for in the loaded textures
     * @return True if it is already loaded, else false.
     */
    bool IsAlreadyLoaded(const char *filename);
    std::map<std::string, std::weak_ptr<SDL_Texture>> loaded_textures;

public:
    Content(SDL_Renderer *render);
    std::shared_ptr<SDL_Texture> LoadTexture(const char *filename, LoadType load_type);
    ~Content();
};
