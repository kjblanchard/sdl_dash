#include <iostream>
#include <supergoon_engine/input/input.hpp>
#include <supergoon_engine/input/player_controller.hpp>

namespace Input
{

    int _numGamePads;
    std::vector<GamePad> _controllerInputs;
    std::vector<GamePad> _lastControllerInputs;
    Uint8 _currentKeyboardState[SDL_NUM_SCANCODES];
    Uint8 _previousKeyboardState[SDL_NUM_SCANCODES];
    std::vector<SDL_GameController *> _connectedControllers;
    std::vector<PlayerController*> PlayerControllers;

    void Startup()
    {
        InitializeKeyboardStateArrays();
        CountPluggedInControllers();
        AddPluggedInControllersToVector();
        InitializeJoystickVectors();

        for (size_t i = 0; i < 4; i++)
        {
            PlayerControllers.push_back(new PlayerController(i));
        }
    }
    void HandleJoystickEvent(const SDL_Event &event)
    {
        switch (event.type)
        {

        case SDL_CONTROLLERDEVICEADDED:
            std::cout << "DEVICEADDED cdevice.which = " << event.cdevice.which << std::endl;
            break;

            // If a controller button is pressed
        case SDL_CONTROLLERBUTTONDOWN:
            // Cycle through the controllers
            for (int i = 0; i < _numGamePads; i++)
            {
                // Looking for the button that was pressed
                if (event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(_connectedControllers[i])))
                {
                    // So the relevant state can be updated
                    _controllerInputs[i].buttons[event.cbutton.button] = true;
                }
            }
            break;

            // Do the same for releasing a button
        case SDL_CONTROLLERBUTTONUP:
            for (int i = 0; i < _numGamePads; i++)
            {
                if (event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(_connectedControllers[i])))
                {
                    _controllerInputs[i].buttons[event.cbutton.button] = false;
                }
            }
            break;

            // And something similar for axis motion
        case SDL_CONTROLLERAXISMOTION:
            for (int i = 0; i < _numGamePads; i++)
            {
                if (event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(_connectedControllers[i])))
                {
                    _controllerInputs[i].axis[event.caxis.axis] = event.caxis.value;
                }
            }
            break;
        default:
            break;
        }
    }

    void InitializeKeyboardStateArrays()
    {
        memset(_previousKeyboardState, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
        memcpy(_currentKeyboardState, SDL_GetKeyboardState(nullptr), sizeof(Uint8) * SDL_NUM_SCANCODES);
    }

    void CountPluggedInControllers()
    {
        int nJoysticks = SDL_NumJoysticks();
        _numGamePads = 0;
        // Count GamePads
        for (int i = 0; i < nJoysticks; i++)
            if (SDL_IsGameController(i))
                _numGamePads++;
    }

    void AddPluggedInControllersToVector()
    {
        // If we have some controllers attached
        if (_numGamePads > 0)
        {
            for (int i = 0; i < _numGamePads; i++)
            {
                // Open the controller and add it to our list
                SDL_GameController *pad = SDL_GameControllerOpen(i);
                if (SDL_GameControllerGetAttached(pad) == 1)
                    _connectedControllers.push_back(pad);
                else
                    std::cout << "Error loading somehow" << std::endl;
                ;
            }
            SDL_GameControllerEventState(SDL_ENABLE);
        }
    }

    void InitializeJoystickVectors()
    {
        _controllerInputs.resize(_numGamePads);
        _lastControllerInputs.resize(_numGamePads);

        for (int i = 0; i < _numGamePads; i++)
        {
            for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
            {
                _controllerInputs[i].axis[a] = 0;
                _lastControllerInputs[i].axis[a] = 0;
            }
            for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
            {
                _controllerInputs[i].buttons[b] = false;
                _lastControllerInputs[i].buttons[b] = false;
            }
        }
    }

    void UpdatePreviousJoystickState()
    {
        for (int i = 0; i < _numGamePads; i++)
        {
            for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
            {
                _lastControllerInputs[i].axis[a] = _controllerInputs[i].axis[a];
            }
            for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
            {
                _lastControllerInputs[i].buttons[b] = _controllerInputs[i].buttons[b];
            }
        }
    }

    bool IsKeyHeldDown(SDL_Scancode key)
    {
        return _previousKeyboardState[key] && _currentKeyboardState[key];
    }

    bool IsKeyHeldDown(int controllerNum, SDL_GameControllerButton button)
    {
        if (_numGamePads == 0 || controllerNum < 0 || controllerNum > _numGamePads)
            return false;

        return _controllerInputs[controllerNum].buttons[button] && _lastControllerInputs[controllerNum].buttons[button];
    }

    bool KeyJustPressed(const SDL_Scancode key)
    {
        return _currentKeyboardState[key] && !_previousKeyboardState[key];
    }

    bool KeyJustPressed(int controllerNum, SDL_GameControllerButton button)
    {
        if (_numGamePads == 0 || controllerNum < 0 || controllerNum > _numGamePads)
            return false;

        return _controllerInputs[controllerNum].buttons[button] && !_lastControllerInputs[controllerNum].buttons[button];
    }

    bool KeyJustReleased(const SDL_Scancode key)
    {
        return !_currentKeyboardState[key] && _previousKeyboardState[key];
    }

    bool KeyJustReleased(int controllerNum, SDL_GameControllerButton button)
    {
        if (_numGamePads == 0 || controllerNum < 0 || controllerNum > _numGamePads)
            return false;

        return !_controllerInputs[controllerNum].buttons[button] && _lastControllerInputs[controllerNum].buttons[button];
    }

    void Input::UpdateKeyboardStates()
    {
        memcpy(_previousKeyboardState, _currentKeyboardState, sizeof(Uint8) * SDL_NUM_SCANCODES);
        memcpy(_currentKeyboardState, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
    }

    PlayerController *Input::GetPlayerController(int controllerToGet)
    {
        return PlayerControllers.at(controllerToGet);
    }

}