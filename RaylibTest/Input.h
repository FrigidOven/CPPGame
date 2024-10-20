#pragma once

#include "Command.h"

enum ControlType
{
	Keyboard,
	Mouse,
	Gamepad
};

enum InputMode
{
	Default = 0
};

struct Input
{
	ControlType controlType;
	int controlValue;
	bool isContinous;

	bool isActive;
	bool isDown;

	Input(ControlType controlType, int controlValue, bool isContinous)
		: controlType(controlType)
		, controlValue(controlValue)
		, isContinous(isContinous)
		, isActive(false)
		, isDown(false)
	{
	}
};