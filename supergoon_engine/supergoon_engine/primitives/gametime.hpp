#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <supergoon_engine_export.h>

class SUPERGOON_ENGINE_EXPORT Gametime
{
private:
    Uint64 start_time;
    Uint64 current_time;

    const double _msPerFrame = 1000.00 / 60;
    double _previousGameRunningTime = 0.0;
    double _currentGameRunningTime = 0.0;
    double _thisTickDeltaTime = 0.0;
    double _timeSinceLastUpdate = 0.0;

public:
    Gametime();
    ~Gametime();
    double ElapsedTimeInSeconds();
    //Hello
    double ElapsedTimeInMilliseconds()
    {
        return _msPerFrame;
    }
    Uint64 TotalGameTimeThisFrame();
    /**
     * Checks to see if we should sleep between frames.  Useful to not have 100% cpu when not using vsync.
     * @return The amount of time that we should sleep on this tick
     */
    ushort CheckForSleepTime();
    /**
     * \brief This function should run all the time to determine if it should run a new frame
     */
    void Tick();
    /**
     * \brief This is called when the game performs a update of the game loop, which will subtract from the amount of time needed to update
     */
    void UpdateClockTimer();
    /**
     * \brief Returns if the time since last update is greater than the ms per frame
     * \return If the game should perform a game loop update
     */
    bool ShouldUpdate() const { return _timeSinceLastUpdate >= _msPerFrame; }
    /**
     * \brief Checks to see if the game is getting a steady frame rate or not
     * \return Value is true if the Update time since last frame is the ms frame time * 1.5
     */
    bool GameIsLagging() const { return _timeSinceLastUpdate >= (_msPerFrame * 1.5); }
    /**
     * \brief Returns the amount of time since the last update was ran
     * \return The amount of time since the last update was ran
     */
    const double &DeltaTime() const { return _timeSinceLastUpdate; }
};