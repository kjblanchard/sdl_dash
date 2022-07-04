#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>

namespace Components
{
    class SUPERGOON_ENGINE_EXPORT SpriteComponent : public Component
    {
    private:
    public:
        Rectangle dst_rect_;
        Rectangle src_rect_;
        SDL_Texture *texture;

    public:
        SpriteComponent(GameObject *owner, SDL_Texture *texture, Point size = Point(), Point src_loc = Point());
        SpriteComponent(GameObject *owner, SDL_Texture *texture, Rectangle src_rectangle);
        SpriteComponent(GameObject *owner, const char* aseprite_file_name);
        ~SpriteComponent() override;
        void Initialize() override;
        void Update(const Gametime &gametime) override;
        void Draw(SDL_Renderer *renderer) override;
    };

}