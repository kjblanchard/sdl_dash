#pragma once
#include <vector>
#include <SDL_gamecontroller.h>
#include <SDL_scancode.h>
#include <SDL_events.h>

struct GamePad
{
    bool buttons[SDL_CONTROLLER_BUTTON_MAX];
    int axis[SDL_CONTROLLER_AXIS_MAX];
};


namespace Input
{
    class PlayerController;

    extern Uint8 _previousKeyboardState[SDL_NUM_SCANCODES];
    extern Uint8 _currentKeyboardState[SDL_NUM_SCANCODES];
    extern std::vector<GamePad> _controllerInputs;
    extern std::vector<GamePad> _lastControllerInputs;
    extern int _numGamePads;
    extern std::vector<SDL_GameController *> _connectedControllers;

    bool IsKeyHeldDown(SDL_Scancode key);
    bool IsKeyHeldDown(int controllerNum, SDL_GameControllerButton button);
    bool KeyJustPressed(SDL_Scancode key);
    bool KeyJustPressed(int controllerNum, SDL_GameControllerButton button);
    bool KeyJustReleased(SDL_Scancode key);
    bool KeyJustReleased(int controllerNum, SDL_GameControllerButton button);

    PlayerController *GetPlayerController(int controllerToGet);
    extern std::vector<PlayerController *> PlayerControllers;

    void Startup();
    /**
     * \brief Handles Joystick events, this assigns them to the Joystick states for reference by the player controllers
     * \param event The event passed from the Game, this should be a joystick event if it gets here
     */
    void HandleJoystickEvent(const SDL_Event &event);
    /**
     * \brief Updates the previous keyboard and current keyboard states
     */
    void UpdateKeyboardStates();
    /**
     * \brief Updates the previous joystick states
     */
    void UpdatePreviousJoystickState();

    void InitializeKeyboardStateArrays();
    void CountPluggedInControllers();
    void AddPluggedInControllersToVector();
    void InitializeJoystickVectors();

}