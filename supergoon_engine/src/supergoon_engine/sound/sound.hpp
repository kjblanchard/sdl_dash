#pragma once
#include <supergoon_engine_export.h>
#include <map>
#include <string>

namespace FMOD
{
    namespace Studio
    {
        class System;
        class EventInstance;
    }
}

class SUPERGOON_ENGINE_EXPORT Sound
{
private:
    static FMOD::Studio::System *loaded_system;
    static FMOD::Studio::EventInstance *current_music;
    static std::map<int, std::string> music_lookup_map;
    static std::map<int, std::string> sfx_lookup_map;

public:
    static bool muted;
    static FMOD::Studio::System *Setup();
    static void PlaySfxOneShot(std::string sound_name);
    static void PlaySfxOneShot(int sound_lookup_int);
    static void PlayBgm(std::string sound_name);
    static void PlayBgm(int sound_lookup_int);
    static void Update();
    static void stop_music_with_fadeout();
    static void restart();

    static inline void AddToGameMusic(std::pair<int, std::string> music)
    {
        music_lookup_map.insert(music);
    }
    static inline void AddToGameSfx(std::pair<int, std::string> music)
    {
        sfx_lookup_map.insert(music);
    }
};