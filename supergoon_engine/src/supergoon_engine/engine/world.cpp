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
#include <supergoon_engine/engine/level_state_machine.hpp>

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

    // TODO do this differently.
    auto sound_table = Lua::LoadLuaTableIntoTempState("./assets/sfx/sfx.lua", "sound", temp_loading_state);
    sol::lua_table sfx_table = (*sound_table)["sound"]["sfx"];
    auto sound_map = Sound::AddToGameSfx;
    sfx_table.for_each([sound_map](std::pair<sol::object, sol::object> key_value_pair)
                       {
                        int key = key_value_pair.first.as<int>();
                        std::string value = key_value_pair.second.as<std::string>();
                        sound_map({key,value}); });

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
    level_state_machine = new LevelStateMachine();
    level_state_machine->ParseLevelTable(level_global_table, content);
    level_state_machine->InitializeStates();
    level_state_machine->ChangeState(1);
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
    Sound::Setup();
    Initialize();
}

void World::Update(Gametime &gametime)
{
    Sound::Update();
    main_camera->Update(gametime);
    // level_state_machine.level->Update(gametime);
    level_state_machine->Update(gametime);
}

void World::Render()
{
    sprite_batch->Begin();
    // level->Draw(*sprite_batch);
    level_state_machine->Draw(*sprite_batch);
    sprite_batch->End();
}
Level *World::GetCurrentLevel()
{
    // return level;
    return level_state_machine->current_state;
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