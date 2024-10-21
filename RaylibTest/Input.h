#pragma once

#include <unordered_set>

class InputSystem;

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
	bool operator==(const Input& other) const
	{
		return controlType == other.controlType && controlValue == other.controlValue;
	}
};

class InputListener
{
private:
	std::unordered_set<KeyboardKey> relevantKeyboardKeys;
	std::unordered_set<GamepadButton> relevantGamepadButtons;
	std::unordered_set<MouseButton> relevantMouseButtons;


	std::vector<KeyboardKey> keyboardKeys;
	std::vector<GamepadButton> gamepadButtons;
	std::vector<MouseButton> mouseButtons;

	std::vector<Input> onCooldownInputs;
	std::vector<float> cooldownTimers;

	void RemoveUpButtons();
	void AddDownButtons(InputSystem* inputSystem);

public:
	void Update(InputSystem* inputSystem);
	bool CheckActive(Input input);
	bool CheckDown(Input input);
	void BlockForSeconds(Input input, float seconds);

	void ListenForInput(Input input);
	void IgnoreInput(Input input);
};