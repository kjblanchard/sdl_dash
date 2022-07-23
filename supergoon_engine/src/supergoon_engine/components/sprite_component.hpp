#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>
#include <supergoon_engine/primitives/sprite.hpp>
#include <memory>

namespace Graphics{
    class SpriteBatch;
}

namespace Components
{
    class SUPERGOON_ENGINE_EXPORT SpriteComponent : public Component
    {
    private:
    public:
        Rectangle temp_dst_rect;
        Rectangle dst_rect_;
        Rectangle src_rect_;
        Sprite sprite;
        int layer;
        bool mirror = false;

    public:
        SpriteComponent(GameObject *owner, std::shared_ptr<SDL_Texture> texture, Point size = Point(), Point src_loc = Point(), int layer = 0);
        SpriteComponent(GameObject *owner, std::shared_ptr<SDL_Texture> texture, Rectangle src_rectangle, int layer = 0);
        ~SpriteComponent() override;
        void Initialize() override;
        void Update(const Gametime &gametime) override;
        void Draw(Graphics::SpriteBatch &spritebatch) override;
        void UpdateFromAnimationComponent(Rectangle src_rectangle);
    };

}