#include <supergoon_engine/engine/level_state_machine.hpp>
#include <sol2/sol.hpp>

void LevelStateMachine::Update(const Gametime &gametime)
{
    if (!current_state)
        return;
    current_state->Update(gametime);
}
void LevelStateMachine::Draw(Graphics::SpriteBatch &spritebatch)
{
    if (!current_state)
        return;

    current_state->Draw(spritebatch);
}

void LevelStateMachine::ParseLevelTable(sol::table &current_level_table, Content *content_ptr)
{
    current_level_table.for_each([content_ptr, this](std::pair<sol::object, sol::object> key_value_pair)
                                 {
            auto table = key_value_pair.second.as<sol::lua_table>();
            if(table != sol::lua_nil)
            {
                auto level = new Level(table, content_ptr);
                AddToStates(level);
            } });
}