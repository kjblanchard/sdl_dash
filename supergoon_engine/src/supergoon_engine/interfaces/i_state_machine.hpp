#pragma once
#include <supergoon_engine_export.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <supergoon_engine/interfaces/i_state.hpp>
#include <supergoon_engine/interfaces/i_initialize.hpp>
#include <supergoon_engine/interfaces/i_update.hpp>
#include <supergoon_engine/interfaces/i_draw.hpp>
#include <supergoon_engine/interfaces/i_tags.hpp>
#include <supergoon_engine/interfaces/i_begin_run.hpp>
#include <supergoon_engine/interfaces/i_reset.hpp>
#include <supergoon_engine/engine/debug.hpp>

namespace Interfaces
{
    template <class T>
    class SUPERGOON_ENGINE_EXPORT IStateMachine : IUpdate, IDraw
    {
    protected:
    public:
        std::vector<std::shared_ptr<IState>> states;
        T *current_state;
        T *previous_state;
        void InitializeStates();
        void AddToStates(IState *state_to_add);
        void ChangeState(int state_id_to_change_to);
        inline void Update(const Gametime &) override {}
        inline void Draw(Graphics::SpriteBatch &) override {}
    };

}

template <class T>
void Interfaces::IStateMachine<T>::InitializeStates()
{
    for (auto &&state : states)
    {
        state->Initialize();
    }
}

template <class T>
void Interfaces::IStateMachine<T>::AddToStates(IState *state_to_add)
{
    states.push_back(std::shared_ptr<IState>(state_to_add));
}
template <class T>
void Interfaces::IStateMachine<T>::ChangeState(int state_id_to_change_to)
{
    auto found_state_it = std::find_if(states.begin(), states.end(), [state_id_to_change_to](std::shared_ptr<IState> state)
                                       {
            if (state_id_to_change_to == state->state_id)
                return true;
            return false; });
    if (found_state_it == states.end())
    {
        Debug::LogWarn("Couldn't find the state in states list.  StateId: %d", state_id_to_change_to);
        return;
    }
    if (current_state)
    {
        auto state_casted = dynamic_cast<IState *>(current_state);
        state_casted->EndState();
    }
    auto dereferenced_state_it = *found_state_it;
    current_state = dynamic_cast<T *>(dereferenced_state_it.get());
    dereferenced_state_it->BeginState();
}