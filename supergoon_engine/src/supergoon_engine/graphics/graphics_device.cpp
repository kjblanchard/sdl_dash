#include <supergoon_engine/graphics/graphics_device.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <sol2/sol.hpp>
#include <SDL.h>

using namespace Graphics;

GraphicsDevice::GraphicsDevice(sol::state *lua_state)
{
    sol::lua_table config_table = (*lua_state)["config"];
    // vsync_enabled = ConfigReader::GetValueFromCfgBool(game_settings_string, vsync_string);
    vsync_enabled = config_table[game_settings_string][vsync_string];
    SDL_DisplayMode displayMode;
    auto result = SDL_GetCurrentDisplayMode(0, &displayMode);
    if(result != 0 )
    {
        printf("Error, %s", SDL_GetError());
        exit(1);
    }
    // fps = (vsync_enabled) ? displayMode.refresh_rate : ConfigReader::GetValueFromCfgInt(game_settings_string,fps_string);
    fps = (vsync_enabled) ? displayMode.refresh_rate : config_table[game_settings_string][fps_string];
    // window_width = ConfigReader::GetValueFromCfgInt(window_ini_section_name, window_width_string);
    window_width = config_table[window_section_name][width_string];
    // window_height = ConfigReader::GetValueFromCfgInt(window_ini_section_name, window_height_string);
    window_height = config_table[window_section_name][height_string];
    // unscaled_width = ConfigReader::GetValueFromCfgInt(window_ini_section_name, game_width_string);
    unscaled_width = config_table[world_section_name][width_string];
    // unscaled_height = ConfigReader::GetValueFromCfgInt(window_ini_section_name, game_height_string);
    unscaled_height = config_table[world_section_name][height_string];
    screen_scale_ratio_width = window_width / static_cast<double>(unscaled_width);
    screen_scale_ratio_height = window_width / static_cast<double>(unscaled_width);
    std::string game_name = config_table[game_settings_string][game_name_string];
    window = SDL_CreateWindow(
    // ConfigReader::GetValueFromCfg(game_settings_string, game_name_string).c_str(),
    // config_table[game_settings_string][game_name_string],
    game_name.c_str(),
        0,
        0,
        window_width,
        window_height,
        0);
    if (!window)
        throw std::runtime_error(SDL_GetError());
    if (vsync_enabled)
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    else
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw std::runtime_error(SDL_GetError());
    // This is SDL's auto resizing.  Logical size causes tearing, but used with integer it looks good but is letterboxed.  I'm handling scaling.
    // Manually inside of the camera class as it was the only one that worked fine.
    // SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
    // SDL_RenderSetLogicalSize(renderer, unscaled_width, unscaled_height);
}

GraphicsDevice::~GraphicsDevice()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void GraphicsDevice::Initialize()
{
}