#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/primitives/gametime.hpp>

Components::AnimationComponent::AnimationComponent(GameObject *owner, const char *aseprite_file_name, int layer_id, Vector2 offset) : Component{owner, offset, 1}, current_animation{""}
{
    aseprite_sheet = std::make_unique<Aseprite::AsepriteSheet>(aseprite_file_name);
    sprite_component = new SpriteComponent(owner, aseprite_sheet->texture, aseprite_sheet->sprite_sheet_frames[0].source_rect, layer_id);
}

void Components::AnimationComponent::Update(const Gametime &gametime)
{
    if (current_animation.name == "")
        return;

    for (auto &&i : current_animation.transitions)
    {
        if (i.transition_function())
        {
            ChangeAnimation(i.new_transition);
            break;
        }
    }

    if (current_animation.looping)
    {
        ms_this_frame += gametime.ElapsedTimeInMilliseconds();
        if (ms_this_frame > aseprite_sheet->sprite_sheet_frames[current_frame_in_animation].millisecond_length)
        {
            ms_this_frame = 0;
            ++current_frame_in_animation;
            if (current_frame_in_animation >= static_cast<int>(current_animation.aseprite_animation.frame_end))
            {
                current_frame_in_animation = current_animation.aseprite_animation.frame_begin;
            }
            dirty = true;
        }
    }

    if (dirty)
    {
        auto frame = aseprite_sheet->sprite_sheet_frames[current_frame_in_animation];
        sprite_component->UpdateFromAnimationComponent(frame.source_rect);
        dirty = false;
    }
}