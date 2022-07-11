#include <supergoon_engine/components/box_collider_component.hpp>

Components::BoxColliderComponent::BoxColliderComponent(GameObject *owner, Point box_size, Vector2 offset) : Component{owner, offset}, size{box_size}
{
}

Components::BoxColliderComponent::~BoxColliderComponent()
{
}
void Components::BoxColliderComponent::Draw(SDL_Renderer * render)
{
    auto rect = GetRectangle().GetSDL_Rect();
    SDL_RenderDrawRect(render,&rect);
}