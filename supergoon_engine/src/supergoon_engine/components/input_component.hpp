#pragma once
#include <supergoon_engine/engine/component.hpp>

namespace Input{
	class Controller;

}

namespace Components
{


	class InputComponent : Component
	{
	public:
		InputComponent(GameObject* owner, Input::Controller *controller);

		void TakeControl(Input::Controller *controllerToUse);

		Input::Controller *CurrentController;
	};
}