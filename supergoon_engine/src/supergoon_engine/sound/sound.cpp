#include <supergoon_engine/sound/sound.hpp>
#include <fmod/fmod.hpp>
#include <fmod/fmod_studio.hpp>
#include <iostream>
#include <supergoon_engine/engine/debug.hpp>

bool Sound::muted = false;
FMOD::Studio::System *Sound::loaded_system = nullptr;
FMOD::Studio::EventInstance *Sound::current_music = nullptr;
std::map<int, std::string> Sound::music_lookup_map;
std::map<int, std::string> Sound::sfx_lookup_map;

void Sound::PlaySfxOneShot(std::string sound_name)
{

    FMOD::Studio::EventDescription *event;
    auto sound = "event:/" + sound_name;
    loaded_system->getEvent(sound.c_str(), &event);
    FMOD::Studio::EventInstance *loaded_event;
    FMOD_RESULT result = event->createInstance(&loaded_event);
    if (result != FMOD_OK)
    {
        Debug::LogError("Could not load event from bank file, Event, %s, FMOD_RESULT: %d", sound.c_str(), result);
        return;
    }
    loaded_event->start();
    loaded_event->release();
}
void Sound::PlaySfxOneShot(int sound_lookup_int)
{
    auto sound = sfx_lookup_map.find(sound_lookup_int);
    if (sound != sfx_lookup_map.end())
        PlaySfxOneShot(sound->second);
    else
    {
        Debug::LogWarn("Sound not found inside of the dict.  Probably need to add it to sfx.lua; Sound Num %d", sound_lookup_int);
    }
}
void Sound::PlayBgm(std::string sound_name)
{
    FMOD::Studio::EventDescription *loadedEventDescription = nullptr;
    auto sound = "event:/" + sound_name;
    auto result = loaded_system->getEvent(sound.c_str(), &loadedEventDescription);
    if (result != FMOD_OK)
        Debug::LogWarn("Could not load bgm event: %s ", sound.c_str());
    FMOD::Studio::EventInstance *loadedEventInstance = nullptr;
    result = loadedEventDescription->createInstance(&loadedEventInstance);
    current_music = loadedEventInstance;
    result = loadedEventInstance->start();
}
void Sound::PlayBgm(int sound_lookup_int)
{
    auto sound = music_lookup_map.find(sound_lookup_int);
    if (sound != sfx_lookup_map.end())
        PlayBgm(sound->second);
}
void Sound::restart()
{
    current_music->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    current_music->start();
}

FMOD::Studio::System *
Sound::Setup()
{
    FMOD::Studio::System *system = nullptr;
    auto result = FMOD::Studio::System::create(&system);
    if (result != FMOD_OK)
        Debug::LogError("Could not create sound system, error code: %d", result);
    FMOD::System *coreSystem = nullptr;
    system->getCoreSystem(&coreSystem);
    coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
    system->initialize(1024, FMOD_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
    FMOD::Studio::Bank *mainBank = nullptr;
    result = system->loadBankFile("assets/sfx/Desktop/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &mainBank);
    // TODO use the strings bank for something.
    FMOD::Studio::Bank *stringsBank = nullptr;
    result = system->loadBankFile("assets/sfx/Desktop/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &mainBank);
    FMOD::ChannelGroup *main_channel_group;
    coreSystem->getMasterChannelGroup(&main_channel_group);
    Sound::loaded_system = system;

    // TODO split this into private function

    return system;
}

void Sound::stop_music_with_fadeout()
{
    current_music->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
}

void Sound::Update()
{
    if (!muted)
        Sound::loaded_system->update();
}