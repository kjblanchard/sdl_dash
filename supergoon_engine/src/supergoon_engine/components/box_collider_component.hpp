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
        inline Rectangle GetRectangle()
        {
            return Rectangle(
                Point((owner_->location.x + static_cast<int>(offset_.x)) * main_camera->GetResolutionScaleSizeX(),
                      (owner_->location.y + static_cast<int>(offset_.y)) * main_camera->GetResolutionScaleSizeY()),
                Point(
                    size.x * main_camera->GetResolutionScaleSizeX(),
                    size.y * main_camera->GetResolutionScaleSizeY()
                ));
        }
        Point size;
        void Update(const Gametime& gametime) override;
        void Draw(Graphics::SpriteBatch&  spritebatch) override;
    };
}