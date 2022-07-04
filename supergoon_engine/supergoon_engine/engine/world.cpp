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
#include <supergoon_engine/tiled/tilemap.hpp>
#include <SDL_image.h>
#include <supergoon_engine/graphics/graphics_device.hpp>
#include <supergoon_engine/graphics/sprite_batch.hpp>
#include <supergoon_engine/objects/camera.hpp>

World *World::instance = nullptr;
World::World() : isRunning{false}, main_camera{nullptr}, config_reader{nullptr}
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

    config_reader = new ConfigReader("cfg.ini");
    graphics = new Graphics::GraphicsDevice(config_reader);
    auto fps = graphics->fps;
    world_gametime = Gametime(fps);
    main_camera = new Camera(Vector2(), graphics);

    isRunning = true;
    content = new Content(graphics->renderer);
    auto tilemap = XmlParser::LoadTiledMap("level_1");
    tiles = Tiled::LoadTilesFromTilemap(tilemap, content);
    auto actor_params = tilemap->actors;
    for (auto &&actor_param : actor_params)
    {
        auto actor = Objects::SpawnActor(actor_param);
        if (actor)
            actors.push_back(actor);
    }

    sprite_batch = new Graphics::SpriteBatch(graphics);
}

void World::InitializeSdl()
{
    auto sdl_video_init_result = SDL_Init(SDL_INIT_VIDEO);
    if (sdl_video_init_result != 0)
        throw std::runtime_error(SDL_GetError());
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
    this_frame_directions.down = this_frame_directions.left = this_frame_directions.up = this_frame_directions.right = false;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A])
    {
        this_frame_directions.left = true;
    }
    if (state[SDL_SCANCODE_D])
    {
        this_frame_directions.right = true;
    }
    if (state[SDL_SCANCODE_W])
    {
        this_frame_directions.up = true;
    }
    if (state[SDL_SCANCODE_S])
    {
        this_frame_directions.down = true;
    }
}

void World::Setup()
{
    Initialize();
    Sound::Setup();
}

void World::Update(Gametime &gametime)
{
    auto speed = 50;

    auto move_speed_right = (this_frame_directions.right) ? gametime.ElapsedTimeInSeconds() * speed : 0;
    auto move_speed_left = (this_frame_directions.left) ? gametime.ElapsedTimeInSeconds() * -speed : 0;
    auto move_speed_up = (this_frame_directions.up) ? gametime.ElapsedTimeInSeconds() * speed : 0;
    auto move_speed_down = (this_frame_directions.down) ? gametime.ElapsedTimeInSeconds() * -speed : 0;
    main_camera->MoveCamera(Vector2(
        move_speed_right + move_speed_left,
        move_speed_up + move_speed_down));

    main_camera->Update(gametime);

    Sound::Update();
    for (auto &&tile : tiles)
    {
        tile->Update(gametime);
    }
    std::for_each(actors.begin(), actors.end(), [&gametime](auto& actor){actor->Update(gametime);});
}

void World::Render()
{
    sprite_batch->Begin();

    for (auto &&tile : tiles)
    {
        sprite_batch->Draw(tile);
    }
    std::for_each(actors.begin(), actors.end(), [&](auto& actor){sprite_batch->Draw(actor);});
    sprite_batch->End();
}

void World::Run()
{
    Setup();
    double previous = SDL_GetTicks64();
    double lag = 0.0;
    while (isRunning)
    {
        double current = SDL_GetTicks64();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;
        ProcessInput();
        while (lag >= world_gametime.ElapsedTimeInMilliseconds())
        {
            printf("\n WorldGamtime: %d, lag: %fUPDATE\n", world_gametime.ElapsedTimeInMilliseconds(), lag);
            Update(world_gametime);
            lag -= world_gametime.ElapsedTimeInMilliseconds();
        }
        Update(world_gametime);
        Render();
        // Sleep until we can update again if not on vsync
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