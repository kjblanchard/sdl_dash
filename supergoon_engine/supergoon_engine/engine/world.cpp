#include <stdexcept>
#include <string>
#include <iostream>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/sound/sound.hpp>
#include <supergoon_engine/primitives/gametime.hpp>
#include <supergoon_engine/ini/config_reader.hpp>
#include <supergoon_engine/xml/xml_parser.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/tiled/tiled_loader.hpp>
#include <SDL_image.h>

World *World::instance = nullptr;
World::World() : isRunning{false}, vsync_enabled{false}, config_reader{nullptr}
{
    if (World::instance == nullptr)
        World::instance = this;
    else
    {
        throw std::runtime_error("World was already created");
    }
}

World::~World()
{
}

void World::Initialize()
{
    config_reader = new ConfigReader("cfg.ini");
    vsync_enabled = ConfigReader::GetValueFromCfgBool("game", "vsync");

    InitializeSdl();

    // TODO Move this to graphics class, this handles the correct fps when reading refresh rate for updates.
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    if (vsync_enabled)
    {
        auto fps = displayMode.refresh_rate;
        // world_gametime = std::make_unique<Gametime>(fps);
        world_gametime = Gametime(fps);
    }
    else
    {
        // world_gametime = std::make_unique<Gametime>(ConfigReader::GetValueFromCfgInt("game", "fps"));
        world_gametime = Gametime(ConfigReader::GetValueFromCfgInt("game", "fps"));
    }

    window_width = ConfigReader::GetValueFromCfgInt(window_ini_section_name, window_width_string);
    window_height = ConfigReader::GetValueFromCfgInt(window_ini_section_name, window_height_string);
    unscaled_width = ConfigReader::GetValueFromCfgInt(window_ini_section_name, game_width_string);
    unscaled_height = ConfigReader::GetValueFromCfgInt(window_ini_section_name, game_height_string);
    screenScaleRatioWidth = window_width / unscaled_width;
    screenScaleRatioHeight = window_width / unscaled_width;

    window = SDL_CreateWindow(
        nullptr,
        0,
        0,
        window_width,
        window_height,
        SDL_WINDOW_OPENGL);
    if (!window)
        throw std::runtime_error(SDL_GetError());
    if (vsync_enabled)
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    else
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw std::runtime_error(SDL_GetError());

    camera.x = 0;
    camera.y = 0;
    camera.w = unscaled_width;
    camera.h = unscaled_height;
    SDL_RenderSetLogicalSize(renderer, unscaled_width, unscaled_height);
    isRunning = true;
    content = new Content(renderer);
    auto tilemap = xml_parser::LoadTiledMap("level_1");
    tiles = TiledLoader::LoadTilesFromTilemap(tilemap);

}

void World::InitializeSdl()
{
    auto sdl_video_init_result = SDL_Init(SDL_INIT_VIDEO);
    if (sdl_video_init_result != 0)
        throw std::runtime_error(SDL_GetError());
        //TODO when adding in ttf, do it here
    // auto sdl_ttf_init_result = TTF_Init();
    // if (sdl_ttf_init_result != 0)
    //     throw std::runtime_error(TTF_GetError());
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags)
    {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }
}

void World::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            break;
        }
    }
}

void World::Setup()
{
    Initialize();
    Sound::Setup();
}

void World::Update(Gametime &gametime)
{
    /// Actually do update stuff
    std::cout << "The update time is " << gametime.ElapsedTimeInSeconds() << "And " << gametime.DeltaTime() << std::endl;
    Sound::Update();
    for (auto &&tile : tiles)
    {
        tile->Update(gametime);
    }

    // tiles->Update(gametime);
}

void World::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    for (auto &&tile : tiles)
    {
        tile->Draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void World::Run()
{
    Setup();
    while (isRunning)
    {

        if (vsync_enabled == false)
        {
            auto wait_time = world_gametime.CheckForSleepTime();

            if (wait_time >= 1 && wait_time <= MILLISECS_PER_FRAME)
                SDL_Delay(wait_time);
        }
        world_gametime.Tick();
        if (world_gametime.ShouldUpdate())
        {
            // TODO move this into a debug class.
            if (world_gametime.GameIsLagging())
                printf("Game is lagging!");
            while (world_gametime.ShouldUpdate())
            {
                ProcessInput();
                Update(world_gametime);
                world_gametime.UpdateClockTimer();
            }
            Render();
        }
    }
}

void World::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}