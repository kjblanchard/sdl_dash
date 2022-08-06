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
    class SUPERGOON_ENGINE_EXPORT FinishAnimationTransition : public Animations::AnimationTransition
    {
        // TODO pass this class by ref in anim component, etc
    public:
        // inline AnimationTransition(std::string transition_to, std::function<bool()> func_to_initiate_change = nullptr, TransitionType type = TransitionType::OnFunction) : new_transition{transition_to}, transition_function{func_to_initiate_change}, type_of_transition{type} {}
        inline FinishAnimationTransition(std::string transition_to, Animations::Animation* thing_to_watch) : AnimationTransition{transition_to}, thing{thing_to_watch} {}
        Animations::Animation* thing;
        ~FinishAnimationTransition() override;
        inline bool ShouldTransition() override
        {
            return thing->ended;
        }
        // bool transition_on_end = false;
        // bool *bool_to_transition = nullptr;
        // TransitionType type_of_transition;
    };

}