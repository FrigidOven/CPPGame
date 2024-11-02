#include "ControllerSystem.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ControllerSystem::Update(Scene& scene, std::vector<Controller>& controllers)
{
	for (auto& controller : controllers)
	{
		controller.up.isDown = CheckDown(controller.playerNumber, controller.up);
		controller.up.isPressed = CheckPressed(controller.playerNumber, controller.up);
		controller.left.isDown = CheckDown(controller.playerNumber, controller.left);
		controller.left.isPressed = CheckPressed(controller.playerNumber, controller.left);
		controller.down.isDown = CheckDown(controller.playerNumber, controller.down);
		controller.down.isPressed = CheckPressed(controller.playerNumber, controller.down);
		controller.right.isDown = CheckDown(controller.playerNumber, controller.right);
		controller.right.isPressed = CheckPressed(controller.playerNumber, controller.right);
	}
}
/*
===================================================================================================
 Private Functions
===================================================================================================
*/
bool ControllerSystem::CheckDown(int playerNumber, Input& input)
{
	switch (input.controlType)
	{
	case ControlType::Keyboard:
		return IsKeyDown(input.controlValue);
	case ControlType::Gamepad:
		return IsGamepadAvailable(playerNumber) && IsGamepadButtonDown(playerNumber, input.controlValue);
	case ControlType::Mouse:
		return IsMouseButtonDown(input.controlValue);
	// The axises will not have a distinction between pressed and down, they can only be "down"
	case ControlType::JoystickPos:
		return IsGamepadAvailable(playerNumber) && GetGamepadAxisMovement(playerNumber, input.controlValue) >= 0.2f; // DEAD-ZONES
	case ControlType::JoystickNeg:
		return IsGamepadAvailable(playerNumber) && GetGamepadAxisMovement(playerNumber, input.controlValue) <= -0.2f; // DEAD-ZONES
	}
	return false;
}
bool ControllerSystem::CheckPressed(int playerNumber, Input& input)
{
	switch (input.controlType)
	{
	case ControlType::Keyboard:
		return IsKeyPressed(input.controlValue);
	case ControlType::Gamepad:
		return IsGamepadAvailable(playerNumber) && IsGamepadButtonPressed(playerNumber, input.controlValue);
	case ControlType::Mouse:
		return IsMouseButtonPressed(input.controlValue);
	}
	return false;
}