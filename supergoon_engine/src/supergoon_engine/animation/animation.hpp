#pragma once
#include <supergoon_engine_export.h>
#include <string>
#include <vector>
#include <supergoon_engine/animation/animation_transition.hpp>

namespace Animations
{
    class SUPERGOON_ENGINE_EXPORT Animation
    {
    public:
        std::string name;
        bool looping;
        std::vector<Animations::AnimationTransition> transitions;
        Animation(std::string name, bool looping = true);

        inline void AddTransition(const Animations::AnimationTransition& transition)
        {
            transitions.push_back(transition);
        }
    };
}