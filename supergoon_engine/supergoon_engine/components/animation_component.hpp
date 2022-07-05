#pragma once
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/engine/component.hpp>

class GameObject;
namespace Aseprite
{
    class AsepriteSheet;
}

namespace Components
{
    class SpriteComponent;
    // private Animator _animator = new Animator();
    // private string _currentAnimationTag;

    class AnimationComponent : public Component
    {

    private:
        SpriteComponent *sprite_component;
        Aseprite::AsepriteSheet *aseprite_sheet;
        float animation_speed = 1.0f;
        double seconds_this_frame = 0.0;

    public:
        AnimationComponent(GameObject *owner, const char *aseprite_file_name, Vector2 offset = Vector2());
        void Update(const Gametime &) override;
        void Draw(SDL_Renderer *) override;
    };
}