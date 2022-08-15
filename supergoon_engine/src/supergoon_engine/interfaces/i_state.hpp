#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/i_initialize.hpp>
#include <supergoon_engine/interfaces/i_update.hpp>
#include <supergoon_engine/interfaces/i_draw.hpp>
#include <supergoon_engine/interfaces/i_tags.hpp>
#include <supergoon_engine/interfaces/i_begin_run.hpp>
#include <supergoon_engine/interfaces/i_reset.hpp>

namespace Interfaces
{
    class SUPERGOON_ENGINE_EXPORT IState : public IInitialize, public IUpdate, public IBeginRun, public IDraw
    {
    public:
        IState(int id) : state_id{id} {}
        int state_id;
        inline void Initialize() override {}
        inline void Update(const Gametime &) override {}
        inline void Draw(Graphics::SpriteBatch &) override {}
        virtual void BeginState();
        inline virtual void EndState() {}
    };

}
