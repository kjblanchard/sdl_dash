#pragma once
#include <supergoon_engine/interfaces/i_initialize.hpp>

namespace sol
{
    class state;

}
struct SDL_Window;
struct SDL_Renderer;

namespace Graphics
{

    class GraphicsDevice : public IInitialize
    {
    private:
        const char *game_name_string = "name";
        const char *fps_string = "fps";
        const char *vsync_string = "vsync";
        const char *game_settings_string = "game";
        const char *world_section_name = "world";
        const char *window_section_name = "window";
        const char *width_string = "width";
        const char *height_string = "height";

        int window_width;
        int window_height;

    public:
        bool vsync_enabled;
        // TODO make this not public
        int unscaled_height;
        int unscaled_width;
        double screen_scale_ratio_width;
        double screen_scale_ratio_height;
        int fps;

        SDL_Window *window;
        SDL_Renderer *renderer;

        GraphicsDevice(sol::state &lua_state);
        void Initialize() override;
        ~GraphicsDevice() override;
    };

}