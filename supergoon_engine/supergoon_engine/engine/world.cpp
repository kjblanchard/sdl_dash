#include <iostream>
#include <stdexcept>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/sound/sound.hpp>
#include <supergoon_engine/primitives/gametime.hpp>
#include <SDL_ttf.h>
#include <SDL_image.h>

World* World::instance = nullptr;
World::World() : isRunning{false}, vsync_enabled{false}
{
    world_gametime = std::make_unique<Gametime>();
    if(World::instance == nullptr)
    World::instance = this;
    else{
        throw std::runtime_error("World was already created");
    }
}

World::~World()
{
}

void World::Initialize()
{
    auto sdl_video_init_result = SDL_Init(SDL_INIT_VIDEO);
    if (sdl_video_init_result != 0)
        throw std::runtime_error(SDL_GetError());
    auto sdl_ttf_init_result = TTF_Init();
    if (sdl_ttf_init_result != 0)
        throw std::runtime_error(TTF_GetError());
    auto sdl_image_init_result = IMG_Init(IMG_INIT_PNG);
    if (sdl_image_init_result == 0)
        throw std::runtime_error(IMG_GetError());

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    // TODO remove the hard coding here.
    windowWidth = 1920;
    windowHeight = 1080;
    unscaledWidth = 256;
    unscaledHeight = 144;
    screenScaleRatioWidth = windowWidth / unscaledWidth;
    screenScaleRatioHeight = windowWidth / unscaledWidth;

    window = SDL_CreateWindow(
        NULL,
        0,
        0,
        windowWidth,
        windowHeight,
        SDL_WINDOW_OPENGL);
    if (!window)
        throw std::runtime_error(SDL_GetError());
    if (vsync_enabled)
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    else
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw std::runtime_error(SDL_GetError());

    // Initialize the camera view with the entire screen area
    camera.x = 0;
    camera.y = 0;
    camera.w = unscaledWidth;
    camera.h = unscaledHeight;
    SDL_RenderSetLogicalSize(renderer, unscaledWidth, unscaledHeight);
    isRunning = true;
}

void World::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        // Handle core SDL events (close window, key pressed, etc.)
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
    Sound::Update();
}

void World::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}
/**
 * Calls setup, and then does a loop of processing input, update, and render.
 */
void World::Run()
{
    Setup();
    while (isRunning)
    {

        if (vsync_enabled == false)
        {
            auto wait_time = world_gametime->CheckForSleepTime();

            if (wait_time >= 1 && wait_time <= MILLISECS_PER_FRAME)
                SDL_Delay(wait_time);
        }
        world_gametime->Tick();
        if (world_gametime->ShouldUpdate())
        {
            // TODO move this into a debug class.
            if (world_gametime->GameIsLagging())
                printf("Game is lagging!");
            while (world_gametime->ShouldUpdate())
            {
                ProcessInput();
                Update(*world_gametime);
                world_gametime->UpdateClockTimer();
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