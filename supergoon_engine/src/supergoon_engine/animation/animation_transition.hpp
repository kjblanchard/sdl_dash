#pragma once
#include <supergoon_engine_export.h>
#include <string>
#include <functional>

namespace Animations
{
    /**
     * An animation transition struct
     * This holds a string which is what the new transition will go to, and a function that returns a bool that will be tested each frame
     */
    struct SUPERGOON_ENGINE_EXPORT AnimationTransition
    {
        inline AnimationTransition(std::string transition_to, std::function<bool()> func_to_initiate_change) : new_transition{transition_to}, transition_function{func_to_initiate_change} {}
        std::string new_transition;
        std::function<bool()> transition_function;
    };
}