#include <supergoon_engine/aseprite/aseprite_sheet.hpp>
#include <SDL.h>
#include <supergoon_engine/engine/content.hpp>
#include <supergoon_engine/engine/world.hpp>

Aseprite::AsepriteSheet::AsepriteSheet(const char* file_name)
{
    std::string suffix = ".png";
    auto full_name = file_name + suffix;
    texture = World::GetWorld()->content->LoadTexture(full_name.c_str(),LoadType::Aseprite);

}