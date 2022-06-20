#include <iostream>
#include <stdexcept>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/sound/sound.hpp>
#include <SDL_ttf.h>
#include <SDL_image.h>

World::World() : isRunning{false}, vsync_enabled{true}
{
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

void World::Update()
{
    // Since we want to only update a specific number of times, lets do some wait time.
    auto total_ticks_update_begin = SDL_GetTicks64();
    if (vsync_enabled == false)
    {
        auto ticks_since_last_update = total_ticks_update_begin - millisecsPreviousFrame;
        auto timeToWait = MILLISECS_PER_FRAME - ticks_since_last_update;
        auto wait_time_int = (int)floor(timeToWait);
        if (wait_time_int >= 1 && wait_time_int <= MILLISECS_PER_FRAME)
        {
            SDL_Delay(wait_time_int);
            total_ticks_update_begin = SDL_GetTicks64();
        }
    }
    auto delta_time_in_ms = (total_ticks_update_begin - millisecsPreviousFrame);
    auto delta_time_in_sec = delta_time_in_ms / 1000.0000;
    std::cout << "Deltat time in ms is " << delta_time_in_ms << "Dalta time in sec is " << delta_time_in_sec << std::endl;
    millisecsPreviousFrame = SDL_GetTicks64();
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
        ProcessInput();
        Update();
        Render();
    }
}

void World::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}