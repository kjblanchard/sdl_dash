#pragma once
#include <SDL.h>
#include <supergoon_engine_export.h>
#include <iostream>

/**
 * Gametime is passed in gameobjects update call for elapsed time this frame. Pass by ref.
 *
 * Besides having elapsed time between frames, gametime is crucial in the world.cpp file for handling sleep time between frames.
 */
class SUPERGOON_ENGINE_EXPORT Gametime
{

private:
    int game_fps = 60;
    Uint64 start_time;
    Uint64 current_time;
    Uint64 previous_game_running_time = 0.0;
    Uint64 current_game_running_time = 0.0;
    Uint64 this_tick_delta_time_ms = 0.0;
    double time_since_last_update = 0.0;

    double MillisecondsPerFrame() const
    {
        return 1000.00 / game_fps;
    }
    /**
     * Change the current games fps.  Used for delay times and time sent to objects update functions.
     * @param fps The amount of fps we should set for update time calculations.
     */
    void SetGameFps(int fps)
    {
        game_fps = fps;
    }

public:
    Gametime(int fps) : Gametime()
    {
        game_fps = fps;
    }
    Gametime();
    /**
     * The amount of seconds in this update tick.  Used by gameobjects when calculating frame independant movement in their update.
     *
     * @return The amount of seconds this update tick (0.016667 for 60 fps, etc)
     */
    double ElapsedTimeInSeconds()
    {
        return MillisecondsPerFrame() / 1000.00;
    }
    /**
     * Gets the amount of milliseconds on this update frame.
     *
     * @return The amount of milliseconds this update frame. 16.6667 for 60fps, etc
     */
   double ElapsedTimeInMilliseconds() const
    {
        return MillisecondsPerFrame();
    }
    /**
     * The total gametime since the game has started in milliseconds.
     * @return The total amount of milliseconds since the game has started.
     */
    Uint64 TotalGameTimeMillisecondsThisFrame();
    /**
     * Checks to see if we should sleep between frames.  Useful to not have 100% cpu when not using vsync.
     * @return The amount of time that we should sleep on this tick
     */
    unsigned short CheckForSleepTime();
    /**
     * This function should run all the time to determine if it should run a new frame
     */
    void Tick();
    /**
     * This is called when the game performs a update of the game loop, which will subtract from the amount of time needed to update
     */
    void UpdateClockTimer();
    /**
     * Returns if the time since last update is greater than the ms per frame
     * @return If the game should perform a game loop update
     */
    bool ShouldUpdate() {

        printf("Time since last update is %f and this needs to be >= %f\n", time_since_last_update, MillisecondsPerFrame());
        return time_since_last_update >= MillisecondsPerFrame(); }
    /**
     *  Checks to see if the game is getting a steady frame rate or not
     * @return Value is true if the Update time since last frame is the ms frame time * 1.5
     */
    bool GameIsLagging() { return time_since_last_update >= (MillisecondsPerFrame() * 1.5); }
    /**
     * Returns the amount of time since the last update was ran
     * @return The amount of time since the last update was ran
     */
    const double &DeltaTime() const { return time_since_last_update; }
};