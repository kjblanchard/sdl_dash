#pragma once
#include <supergoon_engine_export.h>
#include <string>
#include <functional>

namespace Animations
{
    struct SUPERGOON_ENGINE_EXPORT AnimationTransition
    {
        std::string new_transition;
        std::function<bool()> transition_function;
    };
}