#pragma once
#include <sol2/forward.hpp>
#include <json/json.h>

namespace Lua
{

    sol::object json_to_lua(Json::Value value, sol::this_state state);
    sol::object l_read_json(const std::string &path, sol::this_state state);
    sol::object l_parse_json(const std::string &value, sol::this_state state);

}