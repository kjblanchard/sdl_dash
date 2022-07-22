#include <supergoon_engine/aseprite/aseprite_sheet.hpp>
#include <SDL.h>
#include <supergoon_engine/engine/content.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/lua/lua_loader.hpp>

Aseprite::AsepriteSheet::AsepriteSheet(const char* file_name)
{
    std::string suffix = ".png";
    std::string json_suffix = ".json";
    auto full_name = file_name + suffix;
    texture = World::GetWorld()->content->LoadTexture(full_name.c_str(),LoadType::Aseprite);
    Lua::LoadDataFromAsepriteFile(*this, file_name + json_suffix);
    // sprite_sheet_frames = Lua::LoadAsepriteFrames(file_name + json_suffix);


}