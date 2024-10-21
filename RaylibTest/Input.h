#pragma once

#include "Command.h"
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

	void RemoveUpButtons();
	void AddDownButtons(InputSystem* inputSystem);

public:
	void Update(InputSystem* inputSystem);
	bool CheckActive(Input input);
	bool CheckDown(Input input);

	template<typename... KeyboardKey>
	void ListenForKeys(KeyboardKey... keys);

	template<typename... GamepadButton>
	void ListenForGamepadButtons(GamepadButton... buttons);

	template<typename... MouseButton>
	void ListenForMouseButtons(MouseButton... buttons);
};

template<typename... KeyboardKey>
void InputListener::ListenForKeys(KeyboardKey... keys)
{
	(relevantKeyboardKeys.insert(keys), ...);
}

template<typename... GamepadButton>
void InputListener::ListenForGamepadButtons(GamepadButton... buttons)
{
	(relevantGamepadButtons.insert(buttons), ...);
}

template<typename... MouseButton>
void InputListener::ListenForMouseButtons(MouseButton... buttons)
{
	(relevantMouseButtons.insert(buttons), ...);
}