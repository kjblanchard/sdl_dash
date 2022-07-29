#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/animation/animation.hpp>
#include <supergoon_engine/animation/animation_transition.hpp>
#include <supergoon_engine/aseprite/aseprite_sheet.hpp>
#include <supergoon_engine/components/sprite_component.hpp>

class GameObject;
namespace Aseprite
{
    class AsepriteSheet;
}

namespace Components
{

    /**
     * Creates and attaches a sprite component as well, and updates the animation based on the aseprite file loaded.
     */
    class AnimationComponent : public Component
    {
        std::vector<Animations::Animation> animations;
        Animations::Animation current_animation;

    private:
        SpriteComponent *sprite_component;
        std::unique_ptr<Aseprite::AsepriteSheet> aseprite_sheet;
        double ms_this_frame = 0.0;
        int current_frame_in_animation = 0;
        std::string current_animation_name;
        bool dirty = true;

        inline void ChangeAnimation(std::string change)
        {
            current_animation = GetAnimationByName(change);
            current_frame_in_animation = current_animation.aseprite_animation.frame_begin;
            dirty = true;
        }

    public:
        AnimationComponent(GameObject *owner, const char *aseprite_file_name, int layer = 0, Vector2 offset = Vector2());
        void Update(const Gametime &) override;

        inline void ForceAnimationChange(std::string new_anim)
        {
            ChangeAnimation(new_anim);
        }

        inline void AddAnimation(Animations::Animation &animation)
        {
            animation.aseprite_animation = GetAsepriteAnimationByName(animation.name);
            animations.push_back(animation);
        }
        inline Animations::Animation GetAnimationByName(std::string anim_name)
        {
            return *std::find_if(animations.begin(), animations.end(), [&anim_name](const Animations::Animation &anim)
                                 { return anim.name == anim_name; });
        }
        inline Aseprite::AsepriteAnimation GetAsepriteAnimationByName(std::string anim_name)
        {
            return *std::find_if(aseprite_sheet->sprite_sheet_animations.begin(), aseprite_sheet->sprite_sheet_animations.end(), [&anim_name](const Aseprite::AsepriteAnimation &anim)
                                 { return anim.name == anim_name; });
        }
        inline void SetEntryAnim(std::string entry_anim_name)
        {
            current_animation = GetAnimationByName(entry_anim_name);
        }
        inline void SetMirror(bool mirror_val)
        {
            sprite_component->sprite.mirror = mirror_val;
        }
    };
}