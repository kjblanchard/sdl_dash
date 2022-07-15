#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/primitives/vector2.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/objects/camera.hpp>

namespace Components
{
    class BoxColliderComponent : public Component
    {

    public:
        BoxColliderComponent(GameObject *owner, Point box_size, Vector2 offset = Vector2());
        ~BoxColliderComponent() override;
        Rectangle rectangle;
        Rectangle temp_rect;
        SDL_Rect GetCurrentSdlRect();
        void Update(const Gametime &gametime) override;
        void Draw(Graphics::SpriteBatch &spritebatch) override;
    };
}