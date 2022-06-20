#include <supergoon_engine/primitives/gametime.hpp>
#include <iostream>

Gametime::Gametime()
{
    start_time = current_time = SDL_GetTicks64();
}
Gametime::~Gametime()
{
}

void Gametime::Tick()
{
    current_time = SDL_GetTicks64();
    _previousGameRunningTime = _currentGameRunningTime;
    _currentGameRunningTime = current_time;
    _thisTickDeltaTime = _currentGameRunningTime - _previousGameRunningTime;
    _timeSinceLastUpdate += _thisTickDeltaTime;
}

void Gametime::UpdateClockTimer()
{
    _timeSinceLastUpdate -= _msPerFrame;
    if (_timeSinceLastUpdate < 0)
        _timeSinceLastUpdate = 0;
}

ushort Gametime::CheckForSleepTime()
{
    auto timeToWait = _msPerFrame - _timeSinceLastUpdate;
    if (timeToWait < 0)
        return 0;
    auto wait_time_int = static_cast<ushort>(ceil(timeToWait));
    return wait_time_int;
}