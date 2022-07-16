#include <supergoon_engine/input/controller.hpp>

namespace Input
{
    const KeyMapping<SDL_GameControllerButton> *Controller::DefaultJoystickMap = new KeyMapping<SDL_GameControllerButton>{
        SDL_CONTROLLER_BUTTON_DPAD_UP,
        SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        SDL_CONTROLLER_BUTTON_Y,
        SDL_CONTROLLER_BUTTON_B,
        SDL_CONTROLLER_BUTTON_A,
        SDL_CONTROLLER_BUTTON_X,
        SDL_CONTROLLER_BUTTON_START,
        SDL_CONTROLLER_BUTTON_BACK,
    };

    const KeyMapping<SDL_Scancode> *Controller::DefaultKeyboardMap = new KeyMapping<SDL_Scancode>{
        SDL_SCANCODE_UP,
        SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_1,
        SDL_SCANCODE_X,
        SDL_SCANCODE_SPACE,
        SDL_SCANCODE_2,
        SDL_SCANCODE_RETURN,
        SDL_SCANCODE_TAB};

}