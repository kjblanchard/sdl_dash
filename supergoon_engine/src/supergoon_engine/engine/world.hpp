#pragma once
#define SDL_MAIN_HANDLED
#include <memory>
#include <vector>
#include <SDL.h>
#include <supergoon_engine/primitives/gametime.hpp>
#include <supergoon_engine_export.h>

class Content;
class Camera;
class Level;


namespace Graphics
{
    class GraphicsDevice;
    class SpriteBatch;
}

class SUPERGOON_ENGINE_EXPORT World
{

private:
    bool isRunning;

    // TODO store this in a level machine
    Level *level;

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
    Gametime world_gametime;

public:
    World();
    ~World();

    Camera *main_camera;
    Graphics::GraphicsDevice *graphics;
    Content *content;
    inline Level* GetCurrentLevel()
    {
        return level;
    }
    void Run();
    static World *GetWorld()
    {
        return instance;
    }
};
