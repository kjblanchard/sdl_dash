#pragma once
#include <supergoon_engine_export.h>
#include <string>
#include <functional>

namespace Animations
{
    struct SUPERGOON_ENGINE_EXPORT AnimationTransition
    {
        inline AnimationTransition(std::string transition_to, std::function<bool()> func_to_initiate_change) : new_transition{transition_to}, transition_function{func_to_initiate_change} {}

        std::string new_transition;
        std::function<bool()> transition_function;
    };
}