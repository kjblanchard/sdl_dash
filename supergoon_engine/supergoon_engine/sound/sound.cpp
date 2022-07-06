#include <supergoon_engine/sound/sound.hpp>
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <iostream>

bool Sound::muted = false;
FMOD::Studio::System *Sound::loaded_system = nullptr;
FMOD::Studio::EventInstance *Sound::current_music = nullptr;

void Sound::play_sfx_oneshot()
{

    FMOD::Studio::EventDescription *event;
    loaded_system->getEvent("event:/enemy dies", &event);
    FMOD::Studio::EventInstance *loaded_event;
    event->createInstance(&loaded_event);
    loaded_event->start();
}
void Sound::restart()
{
    auto result = current_music->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    result = current_music->start();
}

FMOD::Studio::System *
Sound::Setup()
{
    FMOD::Studio::System *system = nullptr;
    auto result = FMOD::Studio::System::create(&system);
    FMOD::System *coreSystem = nullptr;
    system->getCoreSystem(&coreSystem);
    coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
    system->initialize(1024, FMOD_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
    FMOD::Studio::Bank *mainBank = nullptr;
    result = system->loadBankFile("assets/sfx/Desktop/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &mainBank);
    FMOD::Studio::Bank *stringsBank = nullptr;
    result = system->loadBankFile("assets/sfx/Desktop/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &mainBank);
    FMOD::Studio::EventDescription *loadedEventDescription = nullptr;
    result = system->getEvent("event:/main", &loadedEventDescription);
    FMOD::Studio::EventInstance *loadedEventInstance = nullptr;
    result = loadedEventDescription->createInstance(&loadedEventInstance);
    current_music = loadedEventInstance;
    result = loadedEventInstance->start();

    FMOD::ChannelGroup *main_channel_group;
    coreSystem->getMasterChannelGroup(&main_channel_group);

    std::cout << result;
    Sound::loaded_system = system;
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