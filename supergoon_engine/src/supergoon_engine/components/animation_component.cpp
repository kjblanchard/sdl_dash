#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/components/sprite_component.hpp>
#include <supergoon_engine/aseprite/aseprite_sheet.hpp>

Components::AnimationComponent::AnimationComponent(GameObject *owner, const char *aseprite_file_name, Vector2 offset) : Component{owner, offset}
{
    // auto ase_sheet = Json::LoadAsepriteSheetFromFile(aseprite_file_name);
    // sprite_component = new SpriteComponent(owner, ase_sheet->texture, ase_sheet->sprite_sheet_frames[0].source_rect);
}

void Components::AnimationComponent::Draw(SDL_Renderer *renderer)
{
    sprite_component->Draw(renderer);
}
void Components::AnimationComponent::Update(const Gametime & gametime)
{
    sprite_component->Update(gametime);
}