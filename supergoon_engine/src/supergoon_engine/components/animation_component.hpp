#pragma once
#include <vector>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/animation/animation.hpp>
#include <supergoon_engine/animation/animation_transition.hpp>

class GameObject;
namespace Aseprite
{
    class AsepriteSheet;
}

namespace Components
{
    class SpriteComponent;

    class AnimationComponent : public Component
    {
        std::vector<Animations::Animation> animations;
        Animations::Animation* current_animation = nullptr;

    private:
        SpriteComponent *sprite_component;
        Aseprite::AsepriteSheet *aseprite_sheet;
        double ms_this_frame = 0.0;
        int current_frame_in_animation = 0;

    public:
        AnimationComponent(GameObject *owner, const char *aseprite_file_name, int layer = 0, Vector2 offset = Vector2());
        void Update(const Gametime &) override;
        inline void AddAnimation(Animations::Animation &animation)
        {
            animations.push_back(animation);
        }
    };
}