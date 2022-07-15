#include <supergoon_engine/engine/gameobject.hpp>
#include <SDL_image.h>
#include <iostream>
#include <SDL.h>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/engine/content.hpp>
#include <supergoon_engine/engine/level.hpp>

// statics
World *GameObject::world = nullptr;
Camera *GameObject::main_camera = nullptr;

GameObject::GameObject(Vector2 loc) : IUpdate{}, location{loc}
{
   if (world == nullptr)
      world = World::GetWorld();
   if (main_camera == nullptr)
      main_camera = World::GetWorld()->main_camera;
}

GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
}

void GameObject::Update(const Gametime &gametime)
{
   for (auto &&component : components_)
   {
      component.get()->Update(gametime);
   }
}

void GameObject::Draw(Graphics::SpriteBatch &spritebatch)
{
   for (auto &&component : components_)
   {
      component.get()->Draw(spritebatch);
   }
}

Level *GameObject::GetLevel()
{
   return world->GetCurrentLevel();
}