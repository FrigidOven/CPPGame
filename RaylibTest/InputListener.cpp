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