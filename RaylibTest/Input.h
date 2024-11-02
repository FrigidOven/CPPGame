#pragma once

#include <unordered_set>
#include <raylib.h>

class InputSystem;

enum class ControlType
{
	Keyboard,
	Mouse,
	Gamepad,
	JoystickPos,
	JoystickNeg
};

struct Input
{
	ControlType controlType;
	int controlValue;
	bool isDown;
	bool isPressed;

	Input(ControlType controlType, int controlValue)
		: controlType(controlType)
		, controlValue(controlValue)
		, isDown(false)
		, isPressed(false)
	{
	}
};