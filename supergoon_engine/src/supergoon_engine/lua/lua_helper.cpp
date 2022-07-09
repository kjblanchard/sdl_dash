#include <json/json.h>
#include <fstream>
#include <sstream>
#include <sol2/sol.hpp>
#include <supergoon_engine/lua/lua_helper.hpp>


sol::object Lua::json_to_lua(Json::Value value, sol::this_state state) {
	switch (value.type()) {
	case Json::nullValue:
		return sol::lua_nil;
	case Json::intValue:
	case Json::uintValue:
		return sol::make_object(state.L, value.asInt());
	case Json::realValue:
		return sol::make_object(state.L, value.asDouble());
	case Json::stringValue:
		return sol::make_object(state.L, value.asString());
	case Json::booleanValue:
		return sol::make_object(state.L, value.asBool());
	case Json::arrayValue:
	case Json::objectValue: {
		sol::table table(state.L, sol::create);
		for (Json::Value::const_iterator itr = value.begin();
				itr != value.end(); itr++) {
			if (itr.key().isInt()) {
				table[itr.key().asInt() + 1] = json_to_lua(*itr, state);
			} else {
				table[json_to_lua(itr.key(), state)] = json_to_lua(*itr, state);
			}
		}
		return table;
	}
	}

	assert(false);
}


sol::object Lua::l_parse_json(const std::string &value, sol::this_state state) {
	Json::Value root;
	std::string errors;

	auto reader = Json::CharReaderBuilder().newCharReader();
	bool success = reader->parse(
			value.c_str(),
			value.c_str() + value.size(),
			&root,
			&errors);
	delete reader;

	if (!success) {
		return sol::lua_nil;
	}

	return json_to_lua(root, state);
}

sol::object Lua::l_read_json(const std::string &path, sol::this_state state) {
	Json::Value root;
	{
		std::ifstream is(path);
		is >> root;
	}

	return json_to_lua(root, state);
}