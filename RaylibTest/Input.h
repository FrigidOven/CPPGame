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
	ControlType controlType; // input source
	int controlValue; // input source enum value
	bool isContinuous;

	bool isActive; // should be processed
	bool isDown; // do not use for action handling

	Input(ControlType controlType, int controlValue, bool isContinuous)
		: controlType(controlType)
		, controlValue(controlValue)
		, isContinuous(isContinuous)
		, isActive(false)
		, isDown(false)
	{
	}
};