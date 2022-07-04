#include <supergoon_engine/json/json_parser.hpp>
#include <supergoon_engine/aseprite/aseprite_sheet.hpp>
#include <supergoon_engine/aseprite/aseprite_frame.hpp>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <external/nlohmann/json.hpp>

Aseprite::AsepriteSheet *Json::LoadAsepriteSheetFromFile(const char *filename)
{

    auto aseprite_sheet = new Aseprite::AsepriteSheet(filename);
    std::string prefix = "./assets/actors/";
    std::string suffix = ".json";
    auto full_name = prefix + filename + suffix;
    std::ifstream i(full_name.c_str());
    nlohmann::json j;
    i >> j;
    auto frames = j["frames"];
    for (auto &&frame : frames)
    {
        auto ase_frame = Aseprite::AsepriteFrame();
        ase_frame.millisecond_length = frame["duration"];
        auto frame_data = frame["frame"];
        ase_frame.source_rect = Rectangle(
            Point(frame["frame"]["x"], frame["frame"]["y"]),
            Point(frame_data["w"], frame_data["h"]));
            aseprite_sheet->sprite_sheet_frames.push_back(ase_frame);

    }
    return aseprite_sheet;
}