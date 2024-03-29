#pragma once
#include <supergoon_engine_export.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
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
                FrameBegin,
                End
            };
            EventType type_of_event;
            std::function<void(float, int)> animation_event_func;
        };
        //TODO move this back to private
        bool ended = false;
        std::string name;
        bool looping = true;
        std::vector<AnimationEvent> animation_events;
        std::vector<std::shared_ptr<Animations::AnimationTransition>> transitions;
        Aseprite::AsepriteAnimation aseprite_animation;
        bool random_start_frame = false;

        inline Animation(std::string name_of_anim, bool should_loop = true, bool random_frame_begin = false) : name{name_of_anim}, looping{should_loop}, random_start_frame{random_frame_begin}
        {
        }

        inline void AddTransition(Animations::AnimationTransition *transition)
        {
            transitions.push_back(std::shared_ptr<Animations::AnimationTransition>(transition));
        }

        inline void AddAnimationEvent(AnimationEvent event)
        {
            animation_events.push_back(event);
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

        inline void FireAnimationEvent(AnimationEvent::EventType event_type, float current_time_in_animation = 0, int frane_num = 0)
        {
            std::for_each(animation_events.begin(), animation_events.end(), [event_type, current_time_in_animation, frane_num](AnimationEvent &event)
                          {
                                  if (event.type_of_event == event_type)
                                  {
                                      event.animation_event_func(current_time_in_animation, frane_num);
                                  } });
        }
    };
}