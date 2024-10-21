#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void InputListener::Update(InputSystem* inputSystem)
{
	RemoveUpButtons();
	AddDownButtons(inputSystem);

	// decrement cool down timers
	for (size_t i = 0; i < onCooldownInputs.size(); i++)
	{
		cooldownTimers[i] -= GetFrameTime();
		// if time is up remove from cooldown
		if (cooldownTimers[i] <= 0.0f)
		{
			ListenForInput(onCooldownInputs[i]);
			onCooldownInputs.erase(onCooldownInputs.begin() + i);
			cooldownTimers.erase(cooldownTimers.begin() + i);
			i--;
		}
	}
}
bool InputListener::CheckActive(Input input)
{
	// check if the input is actually active, even if it is being pressed
	switch (input.controlType)
	{
	// TODO: add cases for gamepad and mouse
	case Keyboard:
		bool isActive = keyboardKeys.size() > 0 && keyboardKeys.back() == input.controlValue;

		// non-continuous inputs should only be active for one frame
		if (!input.isContinuous)
			isActive &= !(input.isActive || input.isDown);

		return isActive;
	}
	return false;
}
bool InputListener::CheckDown(Input input)
{
	// check if the input is being pressed, regardless of if it is the last pressed
	switch (input.controlType)
	{
	// TODO: add cases for gamepad and mouse
	case Keyboard:
		return std::find(keyboardKeys.begin(), keyboardKeys.end(), input.controlValue) != keyboardKeys.end();
	}
	return false;
}
void InputListener::BlockForSeconds(Input input, float seconds)
{
	// check if input is already on cool down
	int index = -1;
	for (size_t i = 0; i < onCooldownInputs.size(); i++)
	{
		if (onCooldownInputs[i] == input)
		{
			index = static_cast<int>(i);
			break;
		}
	}
	// if not add it to cooldown list
	if (index == -1)
	{
		onCooldownInputs.push_back(input);
		cooldownTimers.push_back(seconds);
		IgnoreInput(input);
	}
	// if it is then overwrite the timer for that input
	else
		cooldownTimers[index] = seconds;
}
/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void InputListener::RemoveUpButtons()
{
	// doesn't need to use input system, keys will be up regardless

	// removing up keyboard keys
	for (size_t i = 0; i < keyboardKeys.size(); i++)
	{
		if (IsKeyUp(keyboardKeys[i]))
		{
			keyboardKeys.erase(keyboardKeys.begin() + i);
			i--;
		}
	}

	// TODO: remove up gamepad buttons

	// TODO: remove up mouse buttons
}
void InputListener::AddDownButtons(InputSystem* inputSystem)
{
	// read in relevant keyboard keys
	for (auto key : inputSystem->keyboardKeys)
	{
		if (relevantKeyboardKeys.find(key) != relevantKeyboardKeys.end() &&
			std::find(keyboardKeys.begin(), keyboardKeys.end(), key) == keyboardKeys.end())
			keyboardKeys.push_back(key);
	}
	// read in relevent gamepad buttons
	for (auto button : inputSystem->gamepadButtons)
	{
		if (relevantGamepadButtons.find(button) != relevantGamepadButtons.end() &&
			std::find(gamepadButtons.begin(), gamepadButtons.end(), button) == gamepadButtons.end())
			gamepadButtons.push_back(button);
	}
	//read in relevant mouse buttons
	for (auto button : inputSystem->mouseButtons)
	{
		if (relevantMouseButtons.find(button) != relevantMouseButtons.end() &&
			std::find(mouseButtons.begin(), mouseButtons.end(), button) == mouseButtons.end())
			mouseButtons.push_back(button);
	}
}

void InputListener::ListenForInput(Input input)
{
	switch (input.controlType)
	{
	case Keyboard:
		relevantKeyboardKeys.insert(static_cast<KeyboardKey>(input.controlValue));
		break;
	case Gamepad:
		relevantGamepadButtons.insert(static_cast<GamepadButton>(input.controlValue));
		break;
	case Mouse:
		relevantMouseButtons.insert(static_cast<MouseButton>(input.controlValue));
	}
}
void InputListener::IgnoreInput(Input input)
{
	switch (input.controlType)
	{
	case Keyboard:
		relevantKeyboardKeys.erase(static_cast<KeyboardKey>(input.controlValue));
		break;
	case Gamepad:
		relevantGamepadButtons.erase(static_cast<GamepadButton>(input.controlValue));
		break;
	case Mouse:
		relevantMouseButtons.erase(static_cast<MouseButton>(input.controlValue));
	}
}