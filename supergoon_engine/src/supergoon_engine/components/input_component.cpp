#include <supergoon_engine/components/input_component.hpp>
#include <supergoon_engine/input/controller.hpp>

namespace Components
{
    InputComponent::InputComponent(GameObject* owner, Input::Controller *controller) : Component(owner), CurrentController(controller)
    {
    }

    void InputComponent::TakeControl(Input::Controller *controllerToUse)
    {
        CurrentController = controllerToUse;
    }

}