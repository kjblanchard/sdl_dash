#include <stdexcept>
#include <string>
#include <iostream>
#include <SDL_image.h>
#include <sol2/sol.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/sound/sound.hpp>
#include <supergoon_engine/primitives/gametime.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/objects/tile.hpp>
#include <supergoon_engine/tiled/tiled_loader.hpp>
#include <supergoon_engine/tiled/tilemap.hpp>
#include <supergoon_engine/graphics/graphics_device.hpp>
#include <supergoon_engine/graphics/sprite_batch.hpp>
#include <supergoon_engine/objects/camera.hpp>
#include <supergoon_engine/lua/lua_loader.hpp>
#include <supergoon_engine/lua/lua_helper.hpp>
#include <supergoon_engine/engine/level.hpp>
#include <supergoon_engine/input/input.hpp>

World *World::instance = nullptr;
World::World() : isRunning{false}, main_camera{nullptr}
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

    InitializeSdl();
    auto temp_loading_state = new sol::state();
    auto table = Lua::LoadLuaTableIntoTempState("./assets/config/cfg.lua", "config", temp_loading_state);
    auto level_data_name = "levels";
    auto &level_data = Lua::LoadLuaTableIntoGlobalState("./assets/config/levels.lua", level_data_name);
    sol::table level_global_table = level_data[level_data_name]["levels"];

    graphics = new Graphics::GraphicsDevice(table);
    Input::Startup();
    auto fps = graphics->fps;
    world_gametime = Gametime(fps);
    main_camera = new Camera(Vector2(), graphics);
    Sound::muted = (*table)["config"]["sound"]["muted"];
    isRunning = true;
    content = new Content(graphics->renderer);
    sol::table level_1_global_table = level_global_table[1];
    // std::string level_name = level_global_table[1]["name"];

    level = new Level(level_1_global_table, content);
    level->Initialize();

    // auto tilemap = Lua::LoadTiledMap("level_1");
    // tiles = Tiled::LoadTilesFromTilemap(tilemap, content);
    // auto actor_params = tilemap->actors;
    // for (auto &&actor_param : actor_params)
    // {
    //     auto actor = Objects::SpawnActor(actor_param);
    //     if (actor)
    //         actors.push_back(actor);
    // }
    sprite_batch = new Graphics::SpriteBatch(graphics);
}

void World::InitializeSdl()
{
    auto sdl_video_init_result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
    if (sdl_video_init_result != 0)
        throw std::runtime_error(SDL_GetError());
    int flags = IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags)
    {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
    }
}

void World::ProcessInput()
{
    Input::UpdatePreviousJoystickState();

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        if (sdlEvent.type == SDL_KEYDOWN)
        {
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
        }
        else if (sdlEvent.type == SDL_QUIT)
            isRunning = false;
        // else if (sdlEvent.type == SDL_CONTROLLERDEVICEADDED || sdlEvent.type == SDL_CONTROLLERBUTTONDOWN)
        Input::HandleJoystickEvent(sdlEvent);
    }
    Input::UpdateKeyboardStates();
}

void World::Setup()
{
    Initialize();
    Sound::Setup();
}

void World::Update(Gametime &gametime)
{
    Sound::Update();
    main_camera->Update(gametime);
    level->Update(gametime);
}

void World::Render()
{
    sprite_batch->Begin();
    level->Draw(*sprite_batch);
    sprite_batch->End();
}

void World::Run()
{
    Setup();
    Uint64 previous = SDL_GetTicks64();
    double lag = 0.0;
    while (isRunning)
    {
        Uint64 current = SDL_GetTicks64();
        Uint64 elapsed = current - previous;
        previous = current;
        lag += elapsed;
        while (lag >= world_gametime.ElapsedTimeInMilliseconds())
        {
            ProcessInput();
            Update(world_gametime);
            lag -= world_gametime.ElapsedTimeInMilliseconds();
        }

        Render();
        if (graphics->vsync_enabled == false)
        {
            auto wait_time = world_gametime.CheckForSleepTime();

            if (wait_time >= 1 && wait_time <= world_gametime.ElapsedTimeInMilliseconds())
                SDL_Delay(wait_time);
        }
    }
}

void World::Destroy()
{
    delete graphics;
    SDL_Quit();
}