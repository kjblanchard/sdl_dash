#pragma once
#include <supergoon_engine_export.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>
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
    private:

    public:
        struct AnimationEvent
        {
            enum class EventType
            {
                Default,
                Begin,
                Frame,
                End
            };
            EventType type_of_event;
            std::function<void(float)> animation_event_func;
        };
        //TODO move this back to private
        bool ended = false;
        std::string name;
        bool looping = true;
        std::vector<AnimationEvent> animation_events;
        std::vector<std::shared_ptr<Animations::AnimationTransition>> transitions;
        Aseprite::AsepriteAnimation aseprite_animation;

        inline Animation(std::string name_of_anim, bool should_loop = true) : name{name_of_anim}, looping{should_loop}
        {
        }

        inline void AddTransition(Animations::AnimationTransition *transition)
        {
            transitions.push_back(std::shared_ptr<Animations::AnimationTransition>(transition));
        }

        inline bool AnimationEnded()
        {
            return ended;
        }

        inline void AnimationEnd(float time)
        {
            ended = true;
            FireAnimationEvent(AnimationEvent::EventType::End, time);
        }
        inline void AnimationBegin(float time)
        {
            ended = false;
            FireAnimationEvent(AnimationEvent::EventType::Begin, time);
        }

        inline void FireAnimationEvent(AnimationEvent::EventType event_type, float current_time_in_animation)
        {
            std::for_each(animation_events.begin(), animation_events.end(), [event_type, current_time_in_animation](AnimationEvent &event)
                          {
                                  if (event.type_of_event == event_type)
                                  {
                                      event.animation_event_func(current_time_in_animation);
                                  } });
        }
    };
}