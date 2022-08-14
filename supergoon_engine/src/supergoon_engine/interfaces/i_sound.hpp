#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/sound/sound.hpp>

class ISound
{
public:
    inline void StartMusic(int music_to_start)
    {
        Sound::PlayBgm(music_to_start);
    }
    inline void StartMusic(std::string music_to_start)
    {
        Sound::PlayBgm(music_to_start);
    }
    inline void PlaySfxOneShot(int music_to_start)
    {
        Sound::PlaySfxOneShot(music_to_start);
    }
    inline void PlaySfxOneShot(std::string music_to_start)
    {
        Sound::PlaySfxOneShot(music_to_start);
    }
};