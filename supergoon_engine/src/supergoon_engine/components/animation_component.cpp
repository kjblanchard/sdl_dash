#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/primitives/gametime.hpp>
#include <supergoon_engine/engine/debug.hpp>

using namespace Components;

AnimationComponent::AnimationComponent(GameObject *owner, const char *aseprite_file_name, int layer_id, Vector2 offset) : Component{owner, offset, 1}, current_animation{nullptr}
{
    aseprite_sheet = std::make_unique<Aseprite::AsepriteSheet>(aseprite_file_name);
    sprite_component = new SpriteComponent(owner, aseprite_sheet->texture, aseprite_sheet->sprite_sheet_frames[0].source_rect, layer_id);
}

void AnimationComponent::Update(const Gametime &gametime)
{
    if (current_animation == nullptr)
    {
        Debug::LogWarn("Current animation is empty");
        return;
    }

    CheckForAnimationTransitions();
    if (!current_animation->AnimationEnded())
    {
        ms_this_frame += (gametime.ElapsedTimeInMilliseconds() * anim_speed);
        if (FrameJustEnded())
            FrameChange();
        current_animation->FireAnimationEvent(AnimEventType::Frame, ms_this_frame, current_frame_in_animation);
    }

    if (dirty)
        UpdateSpriteComponent();
}
void AnimationComponent::FrameChange()
{
    if (current_frame_in_animation == current_animation->aseprite_animation.frame_end)
    {
        if (current_animation->looping)
        {
            ChangeAnimation(current_animation->name);
        }
        else
        {
            current_animation->AnimationEnd(ms_this_frame);
        }
    }
    else
    {
        ++current_frame_in_animation;
        ms_this_frame = 0;
        dirty = true;
    }
    current_animation->FireAnimationEvent(AnimEventType::FrameBegin, ms_this_frame, current_frame_in_animation - current_animation->aseprite_animation.frame_begin);
}
void AnimationComponent::UpdateSpriteComponent()
{
    auto frame = aseprite_sheet->sprite_sheet_frames[current_frame_in_animation];
    sprite_component->UpdateFromAnimationComponent(frame.source_rect);
    dirty = false;
}
void AnimationComponent::CheckForAnimationTransitions()
{
    for (auto &&i : current_animation->transitions)
    {
        if (i->ShouldTransition())
        {
            ChangeAnimation(i->new_transition);
            SetAnimationSpeed(1.0f);
            break;
        }
    }
}

//TODO should this be called when it is looping?  Problem when using random as it will always start with a random one.
void AnimationComponent::ChangeAnimation(std::string change)
{
    //TODO handle this check better potentially.  This can be null when setting the entry anim at the beginning.
    if (current_animation)
    {
        if (!current_animation->AnimationEnded())
        {
            current_animation->AnimationEnd(static_cast<float>(ms_this_frame));
        }
    }
    if ( !current_animation || current_animation->name != change)
        current_animation = GetAnimationByName(change);
    ms_this_frame = 0;
    auto frame = current_animation->aseprite_animation.frame_begin;
    //TODO made this function better
    if (current_animation->random_start_frame)
    {
        auto upper = current_animation->aseprite_animation.frame_end;
        auto lower = current_animation->aseprite_animation.frame_begin;
        auto modulus = (upper - lower + 1) + lower;
        //TODO seed this
        frame = rand() % modulus;
    }
    current_frame_in_animation = frame;
    current_animation->AnimationBegin(static_cast<float>(ms_this_frame));
    dirty = true;
}