#include <supergoon_engine/input/player_controller.hpp>
#include <supergoon_engine/input/input.hpp>

namespace Input
{
	PlayerController::PlayerController(int num)
	{
		_playerNum = num;
	}
	bool PlayerController::IsButtonPressed(ControllerButtons controllerButton)
	{
		switch (controllerButton)
		{
		case ControllerButtons::Default:
			return false;
		case ControllerButtons::Up:
			return Input::KeyJustPressed(_keyboardMapping.UpButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.UpButton);
		case ControllerButtons::Right:
			return Input::KeyJustPressed(_keyboardMapping.RightButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.RightButton);
		case ControllerButtons::Down:
			return Input::KeyJustPressed(_keyboardMapping.DownButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.DownButton);
		case ControllerButtons::Left:
			return Input::KeyJustPressed(_keyboardMapping.LeftButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.LeftButton);
		case ControllerButtons::Y:
			return Input::KeyJustPressed(_keyboardMapping.YButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.YButton);
		case ControllerButtons::B:
			return Input::KeyJustPressed(_keyboardMapping.BButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.BButton);
		case ControllerButtons::A:
			return Input::KeyJustPressed(_keyboardMapping.AButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.AButton);
		case ControllerButtons::X:
			return Input::KeyJustPressed(_keyboardMapping.XButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.XButton);
		case ControllerButtons::Start:
			return Input::KeyJustPressed(_keyboardMapping.StartButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.StartButton);
		case ControllerButtons::Select:
			return Input::KeyJustPressed(_keyboardMapping.SelectButton) || Input::KeyJustPressed(_playerNum, _joystickMapping.SelectButton);
		}
		return false;
	}

	bool PlayerController::IsButtonHeld(ControllerButtons controllerButton)
	{
		switch (controllerButton)
		{
		case ControllerButtons::Default:
			return false;
		case ControllerButtons::Up:
			return Input::IsKeyHeldDown(_keyboardMapping.UpButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.UpButton);
		case ControllerButtons::Right:
			return Input::IsKeyHeldDown(_keyboardMapping.RightButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.RightButton);
		case ControllerButtons::Down:
			return Input::IsKeyHeldDown(_keyboardMapping.DownButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.DownButton);
		case ControllerButtons::Left:
			return Input::IsKeyHeldDown(_keyboardMapping.LeftButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.LeftButton);
		case ControllerButtons::Y:
			return Input::IsKeyHeldDown(_keyboardMapping.YButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.YButton);
		case ControllerButtons::B:
			return Input::IsKeyHeldDown(_keyboardMapping.BButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.BButton);
		case ControllerButtons::A:
			return Input::IsKeyHeldDown(_keyboardMapping.AButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.AButton);
		case ControllerButtons::X:
			return Input::IsKeyHeldDown(_keyboardMapping.XButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.XButton);
		case ControllerButtons::Start:
			return Input::IsKeyHeldDown(_keyboardMapping.StartButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.StartButton);
		case ControllerButtons::Select:
			return Input::IsKeyHeldDown(_keyboardMapping.SelectButton) || Input::IsKeyHeldDown(_playerNum, _joystickMapping.SelectButton);
		}
		return false;
	}

	bool PlayerController::IsButtonReleased(ControllerButtons controllerButton)
	{
		switch (controllerButton)
		{
		case ControllerButtons::Default:
			return false;
		case ControllerButtons::Up:
			return Input::KeyJustReleased(_keyboardMapping.UpButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.UpButton);
		case ControllerButtons::Right:
			return Input::KeyJustReleased(_keyboardMapping.RightButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.RightButton);
		case ControllerButtons::Down:
			return Input::KeyJustReleased(_keyboardMapping.DownButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.DownButton);
		case ControllerButtons::Left:
			return Input::KeyJustReleased(_keyboardMapping.LeftButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.LeftButton);
		case ControllerButtons::Y:
			return Input::KeyJustReleased(_keyboardMapping.YButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.YButton);
		case ControllerButtons::B:
			return Input::KeyJustReleased(_keyboardMapping.BButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.BButton);
		case ControllerButtons::A:
			return Input::KeyJustReleased(_keyboardMapping.AButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.AButton);
		case ControllerButtons::X:
			return Input::KeyJustReleased(_keyboardMapping.XButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.XButton);
		case ControllerButtons::Start:
			return Input::KeyJustReleased(_keyboardMapping.StartButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.StartButton);
		case ControllerButtons::Select:
			return Input::KeyJustReleased(_keyboardMapping.SelectButton) || Input::KeyJustReleased(_playerNum, _joystickMapping.SelectButton);
		}
		return false;
	}

}