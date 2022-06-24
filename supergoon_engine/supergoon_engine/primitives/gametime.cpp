#include <supergoon_engine/primitives/gametime.hpp>
#include <iostream>
#include <cmath>

Gametime::Gametime() : start_time{SDL_GetTicks64()}, current_time{SDL_GetTicks64()}
{
}

void Gametime::Tick()
{
    current_time = SDL_GetTicks64();
    previous_game_running_time = current_game_running_time;
    current_game_running_time = current_time;
    this_tick_delta_time = current_game_running_time - previous_game_running_time;
    time_since_last_update += this_tick_delta_time;
}

void Gametime::UpdateClockTimer()
{
    time_since_last_update -= MillisecondsPerFrame();
    if (time_since_last_update < 0)
        time_since_last_update = 0;
}

unsigned short Gametime::CheckForSleepTime()
{
    auto timeToWait = MillisecondsPerFrame() - time_since_last_update;
    if (timeToWait < 0)
        return 0;
    auto wait_time_int = static_cast<unsigned short>(floor(timeToWait));
    return wait_time_int;
}