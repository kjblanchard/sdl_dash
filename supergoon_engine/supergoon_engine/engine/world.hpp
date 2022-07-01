#pragma once
#define SDL_MAIN_HANDLED
#include <memory>
#include <vector>
#include <SDL.h>
#include <supergoon_engine/primitives/gametime.hpp>
#include <supergoon_engine_export.h>

class Tile;
class Content;
class ConfigReader;
// TODO remove this

class SUPERGOON_ENGINE_EXPORT World
{
private:
    bool isRunning;
    bool vsync_enabled;
    Gametime world_gametime;

    SDL_Window *window;
    SDL_Renderer *renderer;

    // TODO remove this
    std::vector<Tile*> tiles;


    const char *window_ini_section_name = "window";
    const char *window_width_string = "window_width";
    const char *window_height_string = "window_height";
    const char *game_width_string = "game_width";
    const char *game_height_string = "game_height";

    void InitializeSdl();

protected:
    void Initialize();
    void Setup();
    void ProcessInput();
    void Update(Gametime &gametime);
    void Render();
    void Destroy();

    int window_width;
    int window_height;
    int unscaled_height;
    int unscaled_width;
    int screenScaleRatioWidth;
    int screenScaleRatioHeight;

    const int FPS = 60;
    const double MILLISECS_PER_FRAME = 1000.0000 / FPS;
    static World *instance;

public:
    World();
    ~World();

    Content *content;
    void Run();
    ConfigReader *config_reader;
    static World *GetWorld()
    {
        return instance;
    }
    //TODO probably mane this not public
    SDL_Rect camera;

};
