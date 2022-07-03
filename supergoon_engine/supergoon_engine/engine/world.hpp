#pragma once
// #define SDL_MAIN_HANDLED
#include <memory>
#include <vector>
#include <SDL.h>
#include <supergoon_engine/primitives/gametime.hpp>
#include <supergoon_engine_export.h>

class Tile;
class Content;
class ConfigReader;
class Camera;

namespace Graphics
{
    class GraphicsDevice;
    class SpriteBatch;
}

class SUPERGOON_ENGINE_EXPORT World
{
    struct dir
    {
        bool up, down, left, right = false;
    };

private:
    bool isRunning;
    bool vsync_enabled;
    dir this_frame_directions;
    Gametime world_gametime;

    // TODO remove this
    std::vector<Tile *> tiles;
    void InitializeSdl();

protected:
    void Initialize();
    void Setup();
    void ProcessInput();
    void Update(Gametime &gametime);
    void Render();
    void Destroy();
    Graphics::SpriteBatch *sprite_batch;
    static World *instance;

public:
    World();
    ~World();

    // TODO make this not public
    Camera* main_camera;
    Graphics::GraphicsDevice *graphics;
    Content *content;
    void Run();
    ConfigReader *config_reader;
    static World *GetWorld()
    {
        return instance;
    }
};
