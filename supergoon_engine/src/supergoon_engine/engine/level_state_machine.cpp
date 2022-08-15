#include <supergoon_engine/engine/level_state_machine.hpp>

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