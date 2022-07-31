#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/animation/animation.hpp>
#include <functional>

namespace Animations
{
    /**
     * An animation transition struct
     * This holds a string which is what the new transition will go to, and a function that returns a bool that will be tested each frame
     */
    class SUPERGOON_ENGINE_EXPORT FunctionAnimationTransition : public Animations::AnimationTransition
    {
        // TODO pass this class by ref in anim component, etc
    public:
        // inline AnimationTransition(std::string transition_to, std::function<bool()> func_to_initiate_change = nullptr, TransitionType type = TransitionType::OnFunction) : new_transition{transition_to}, transition_function{func_to_initiate_change}, type_of_transition{type} {}
        inline FunctionAnimationTransition(std::string transition_to, std::function<bool()> func_to_initiate_change) : AnimationTransition{transition_to}, change_func{func_to_initiate_change} {}
        std::function<bool()> change_func;
        inline bool ShouldTransition() override
        {
            return change_func();
        }
        // bool transition_on_end = false;
        // bool *bool_to_transition = nullptr;
        // TransitionType type_of_transition;
    };

}