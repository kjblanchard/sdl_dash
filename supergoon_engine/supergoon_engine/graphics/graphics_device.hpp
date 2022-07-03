#pragma once
#include <supergoon_engine/interfaces/i_initialize.hpp>

class ConfigReader;
struct SDL_Window;
struct SDL_Renderer;

namespace Graphics
{

    class GraphicsDevice : public IInitialize
    {
    private:
        bool vsync_enabled;
        const char *window_ini_section_name = "window";
        const char *window_width_string = "window_width";
        const char *window_height_string = "window_height";
        const char *game_width_string = "game_width";
        const char *game_height_string = "game_height";

        int window_width;
        int window_height;

    public:
        // TODO make this not public
        int unscaled_height;
        int unscaled_width;
        double screenScaleRatioWidth;
        double screenScaleRatioHeight;

        SDL_Window *window;
        SDL_Renderer *renderer;

        GraphicsDevice(ConfigReader *config);
        void Initialize() override;
        ~GraphicsDevice() override;
    };

}