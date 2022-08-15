#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/i_state_machine.hpp>
#include <supergoon_engine/engine/level.hpp>

class LevelStateMachine : public Interfaces::IStateMachine<Level>
{
public:
    void Update(const Gametime &) override;
    void Draw(Graphics::SpriteBatch &) override;
};