#pragma once
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>

namespace Input
{
    enum class ControllerButtons
    {
        Default = 0,
        Up = 1,
        Right = 2,
        Down = 3,
        Left = 4,
        Y = 5,
        B = 6,
        A = 7,
        X = 8,
        Start = 9,
        Select = 10,
    };

    template <typename T>
    class KeyMapping
    {
    public:
        T UpButton;
        T RightButton;
        T DownButton;
        T LeftButton;
        T YButton;
        T BButton;
        T AButton;
        T XButton;
        T StartButton;
        T SelectButton;
    };

    class Controller
    {
    public:
        virtual ~Controller() = default;
        virtual bool IsButtonPressed(ControllerButtons controllerButton) = 0;
        virtual bool IsButtonReleased(ControllerButtons controllerButton) = 0;
        virtual bool IsButtonHeld(ControllerButtons controllerButton) = 0;

    protected:
        static const KeyMapping<SDL_Scancode> *DefaultKeyboardMap;
        static const KeyMapping<SDL_GameControllerButton> *DefaultJoystickMap;
    };
}