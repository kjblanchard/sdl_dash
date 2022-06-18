#include <iostream>
// #include <stdexcept>
#include <supergoon_engine/engine/world.hpp>

World::World() : isRunning{false}
{
    // assetStore = std::make_unique<AssetStore>();
    std::cout << "Making a world..." << std::endl;
}

World::~World()
{
}

// int World::windowWidth;
// int World::windowHeight;
// int World::mapWidth;
// int World::mapHeight;
// int World::unscaledHeight;
// int World::unscaledWidth;
// int World::screenScaleRatioHeight;
// int World::screenScaleRatioWidth;
// bool World::isDebug = false;
// SDL_Renderer *World::renderer;


// void World::Initialize()
// {
//     if (SDL_Init(SDL_INIT_VIDEO) != 0)
//         throw std::runtime_error(SDL_GetError());
//     // if (TTF_Init() != 0)
//     //     throw std::runtime_error(TTF_GetError());

//     SDL_DisplayMode displayMode;
//     SDL_GetCurrentDisplayMode(0, &displayMode);

//     // windowWidth = window_config[windowWidthStr];
//     // windowHeight = window_config[windowHeightStr];
//     // unscaledWidth = window_config[unscaledWidthStr];
//     // unscaledHeight = window_config[unscaledHeightStr];
//     // screenScaleRatioWidth = windowWidth / unscaledWidth;
//     // screenScaleRatioHeight = windowWidth / unscaledWidth;

//     window = SDL_CreateWindow(
//         NULL,
//         0,
//         0,
//         512,
//         288,
//         SDL_WINDOW_OPENGL);
//     if (!window)
//         throw std::runtime_error(SDL_GetError());
//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if (!renderer)
//         throw std::runtime_error(SDL_GetError());

//     // Initialize the camera view with the entire screen area
//     camera.x = 0;
//     camera.y = 0;
//     camera.w = unscaledWidth;
//     camera.h = unscaledHeight;
//     SDL_RenderSetLogicalSize(renderer, unscaledWidth, unscaledHeight);
//     SDL_RenderSetVSync(renderer, 1);

//     isRunning = true;
// }

// void World::ProcessInput()
// {
//     SDL_Event sdlEvent;
//     while (SDL_PollEvent(&sdlEvent))
//     {
//         ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
//         // Handle core SDL events (close window, key pressed, etc.)
//         switch (sdlEvent.type)
//         {
//         case SDL_QUIT:
//             isRunning = false;
//             break;
//         case SDL_KEYDOWN:
//             if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
//             {
//                 isRunning = false;
//             }
//             break;
//         }
//     }
// }

// void World::Setup()
// {

// }

// void World::Update()
// {
//     // int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
//     // if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
//     //     SDL_Delay(5);
//     // double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
//     // millisecsPreviousFrame = SDL_GetTicks();
// }

// void World::Render()
// {
//     SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
//     SDL_RenderClear(renderer);

//     SDL_RenderPresent(renderer);
// }

// void World::Run()
// {
//     Setup();
//     while (isRunning)
//     {
//         ProcessInput();
//         Update();
//         Render();
//     }
// }

// void World::Destroy()
// {
//     ImGui_ImplSDLRenderer_Shutdown();
//     ImGui_ImplSDL2_Shutdown();
//     ImGui::DestroyContext();

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }