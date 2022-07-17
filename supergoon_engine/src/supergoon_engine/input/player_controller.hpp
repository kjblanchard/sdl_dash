#pragma once
#include <supergoon_engine_export.h>

#include <supergoon_engine/input/controller.hpp>

namespace Input
{
    class SUPERGOON_ENGINE_EXPORT  PlayerController : public Controller
    {
    public:
        PlayerController()
        {
        }
        PlayerController(int num);
        bool IsButtonPressed(ControllerButtons controllerButton) override;
        bool IsButtonHeld(ControllerButtons controllerButton) override;
        bool IsButtonReleased(ControllerButtons controllerButton) override;

        void UpdateControllerMapping(KeyMapping<SDL_Scancode> newKeyboardMap)
        {
            _keyboardMapping = newKeyboardMap;
        }
        void UpdateControllerMapping(KeyMapping<SDL_GameControllerButton> newJoystickMap)
        {
            _joystickMapping = newJoystickMap;
        }

        void UpdateControlType(bool isUsingGamepad)
        {
            _isUsingGamePad = isUsingGamepad;
        }

        void UpdatePlayerNum(uint8_t playerNum)
        {
            _playerNum = playerNum;
        }

    private:
        KeyMapping<SDL_Scancode> _keyboardMapping{*DefaultKeyboardMap};
        KeyMapping<SDL_GameControllerButton> _joystickMapping{*DefaultJoystickMap};
        bool _isUsingGamePad{false};
        unsigned char _playerNum{0};
    };

}
