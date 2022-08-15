#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/i_state_machine.hpp>
#include <supergoon_engine/engine/level.hpp>
#include <sol2/forward.hpp>

class Content;
class LevelStateMachine : public Interfaces::IStateMachine<Level>
{
public:
    void ParseLevelTable(sol::table &current_level_table, Content *content_ptr);
    void Update(const Gametime &) override;
    void Draw(Graphics::SpriteBatch &) override;
};