#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class World
{
private:
    bool isRunning;
    int millisecsPreviousFrame = 0;
    SDL_Window *window;
    // SDL_Renderer *renderer;
    SDL_Rect camera;


    const char *windowWidthStr = "window_width";
    const char *windowHeightStr = "window_height";
    const char *unscaledWidthStr = "unscaled_width";
    const char *unscaledHeightStr = "unscaled_height";


public:
    World();
    ~World();
    void Initialize();
    void Run();
    void Setup();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
    static SDL_Renderer *renderer;

    static int windowWidth;
    static int windowHeight;
    static int unscaledHeight;
    static int unscaledWidth;
    static int mapWidth;
    static int mapHeight;
    static int screenScaleRatioWidth;
    static int screenScaleRatioHeight;
    static bool isDebug;
};
