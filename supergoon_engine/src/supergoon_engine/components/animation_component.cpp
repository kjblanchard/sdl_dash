#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/primitives/gametime.hpp>

using namespace Components;

AnimationComponent::AnimationComponent(GameObject *owner, const char *aseprite_file_name, int layer_id, Vector2 offset) : Component{owner, offset, 1}, current_animation{nullptr}
{
    aseprite_sheet = std::make_unique<Aseprite::AsepriteSheet>(aseprite_file_name);
    sprite_component = new SpriteComponent(owner, aseprite_sheet->texture, aseprite_sheet->sprite_sheet_frames[0].source_rect, layer_id);
}

void AnimationComponent::Update(const Gametime &gametime)
{
    // TODO debug log this.
    if (current_animation == nullptr)
        return;

    CheckForAnimationTransitions();
    if (!current_animation->AnimationEnded())
    {
        ms_this_frame += gametime.ElapsedTimeInMilliseconds();
        if (FrameJustEnded())
            FrameChange();
        current_animation->FireAnimationEvent(AnimEventType::Frame, ms_this_frame);
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
            break;
        }
    }
}

void AnimationComponent::ChangeAnimation(std::string change)
{
    // TODO check to see if current animation exists.
    if (!current_animation->AnimationEnded())
    {
        current_animation->AnimationEnd(static_cast<float>(ms_this_frame));
    }
    if (current_animation->name != change)
        current_animation = GetAnimationByName(change);
    ms_this_frame = 0;
    current_frame_in_animation = current_animation->aseprite_animation.frame_begin;
    current_animation->AnimationBegin(static_cast<float>(ms_this_frame));
    dirty = true;
}