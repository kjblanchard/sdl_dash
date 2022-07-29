#pragma once
#include <supergoon_engine_export.h>
#include <string>
#include <vector>
#include <supergoon_engine/animation/animation_transition.hpp>
#include <supergoon_engine/aseprite/aseprite_animation.hpp>

namespace Animations
{
    /**
     * An animation.  This animation will hold a vector of all of the different transitions that it can perform, as well if it should loop and the transitions name.
     *
     */
    class SUPERGOON_ENGINE_EXPORT Animation
    {
    public:
        std::string name;
        bool looping;
        std::vector<Animations::AnimationTransition> transitions;
        Aseprite::AsepriteAnimation aseprite_animation;

        inline Animation(std::string name_of_anim, bool should_loop = true) : name{name_of_anim}, looping{should_loop}
        {
        }

        inline void AddTransition(const Animations::AnimationTransition &transition)
        {
            transitions.push_back(transition);
        }
    };
}