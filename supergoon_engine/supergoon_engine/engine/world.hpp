#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <supergoon_engine_export.h>

class SUPERGOON_ENGINE_EXPORT World
{
private:
    bool isRunning;
    bool vsync_enabled;
    Uint64 millisecsPreviousFrame = 0;
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
    void Update();
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

public:
    World();
    ~World();
    void Run();
};
