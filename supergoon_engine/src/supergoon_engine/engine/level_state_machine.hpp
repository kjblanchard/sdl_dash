#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/i_state_machine.hpp>
#include <supergoon_engine/engine/level.hpp>
#include <sol2/forward.hpp>

class Content;
/**
 * @brief This is a state machine that holds all of the different levels in the game.
 *
 */
class LevelStateMachine : public Interfaces::IStateMachine<Level>

{
public:
    /**
     * @brief Loops through the passed in table, and creates levels for each one.
     *
     * @param current_level_table The loaded lua table that contains all of the levels
     * @param content_ptr Pointer to the content so that the levels can load
     */
    void ParseLevelTable(sol::table &current_level_table, Content *content_ptr);
    void Update(const Gametime &) override;
    void Draw(Graphics::SpriteBatch &) override;
};