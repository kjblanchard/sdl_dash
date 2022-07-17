#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/aseprite/aseprite_sheet.hpp>
#include <supergoon_engine/primitives/gametime.hpp>

Components::AnimationComponent::AnimationComponent(GameObject *owner, const char *aseprite_file_name, int layer_id, Vector2 offset) : Component{owner, offset}
{
    aseprite_sheet = new Aseprite::AsepriteSheet(aseprite_file_name);
    sprite_component = new SpriteComponent(owner, aseprite_sheet->texture, aseprite_sheet->sprite_sheet_frames[0].source_rect,layer_id);
}

void Components::AnimationComponent::Update(const Gametime &gametime)
{
    ms_this_frame += gametime.ElapsedTimeInMilliseconds();
    if (ms_this_frame > aseprite_sheet->sprite_sheet_frames[current_frame_in_animation].millisecond_length)
    {
        ms_this_frame = 0;
        ++current_frame_in_animation;
        if (current_frame_in_animation >= static_cast<int>(aseprite_sheet->sprite_sheet_frames.size()))
        {
            current_frame_in_animation = 0;
        }
        auto frame = aseprite_sheet->sprite_sheet_frames[current_frame_in_animation];
        sprite_component->UpdateFromAnimationComponent(frame.source_rect);
    }
    sprite_component->Update(gametime);
}