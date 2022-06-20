#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <supergoon_engine_export.h>
#include <memory>

class Gametime;
class SUPERGOON_ENGINE_EXPORT World
{
private:
    bool isRunning;
    bool vsync_enabled;
    // double gametime_residual = 0.0;
    // Uint64 millisecsPreviousFrame = 0;
    std::unique_ptr<Gametime> world_gametime;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect camera;

    const char *windowWidthStr = "window_width";
    const char *windowHeightStr = "window_height";
    const char *unscaledWidthStr = "unscaled_width";
    const char *unscaledHeightStr = "unscaled_height";

protected:
    void Initialize();
    void Setup();
    void ProcessInput();
    void Update(Gametime &gametime);
    void Render();
    void Destroy();

    int windowWidth;
    int windowHeight;
    int unscaledHeight;
    int unscaledWidth;
    int mapWidth;
    int mapHeight;
    int screenScaleRatioWidth;
    int screenScaleRatioHeight;

    const int FPS = 60;
    const double MILLISECS_PER_FRAME = 1000.0000 / FPS;
    static World* instance;

public:
    World();
    ~World();
    void Run();
    static World* GetWorld()
    {
        return instance;
    }
};
