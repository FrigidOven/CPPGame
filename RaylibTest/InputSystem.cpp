#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
InputSystem::InputSystem(InputMode inputMode)
	: inputMode(inputMode)
{
}
void InputSystem::Update(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents)
{

	RemoveKeys();
	AddKeys();

	switch (inputMode)
	{
	case Default:
		UpdatePlayerInputListeners(scene, playerInputListenerComponents);
		break;
	}
}

/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void InputSystem::RemoveKeys()
{
	for (size_t i = 0; i < keyboardKeys.size(); i++)
	{
		if (IsKeyUp(keyboardKeys[i]))
		{
			keyboardKeys.erase(keyboardKeys.begin() + i);
			i--;
		}
	}
}
void InputSystem::AddKeys()
{
	KeyboardKey key = KEY_NULL;
	do
	{
		key = static_cast<KeyboardKey>(GetKeyPressed());
		if (key != KEY_NULL && std::find(keyboardKeys.begin(), keyboardKeys.end(), key) == keyboardKeys.end())
			keyboardKeys.push_back(key);

	} while (key != KEY_NULL);
}

bool InputSystem::CheckActive(Input input)
{
	// check if the input is actually active, even if it is being pressed
	switch (input.controlType)
	{
	case Keyboard:
		bool isActive = keyboardKeys.size() > 0 && keyboardKeys.back() == input.controlValue;

		// non-continuous inputs should only be active for one frame
		if (!input.isContinuous)
			isActive &= !(input.isActive || input.isDown);

		return isActive;
	}
}
bool InputSystem::CheckDown(Input input)
{
	// check if the input is being pressed, regardless of if it is the last pressed
	switch (input.controlType)
	{
	case Keyboard:
		return std::find(keyboardKeys.begin(), keyboardKeys.end(), input.controlValue) != keyboardKeys.end();
	}
}


void InputSystem::UpdatePlayerInputListeners(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents)
{
	for (auto& playerInputListener : playerInputListenerComponents)
	{
		// check active before checking down, otherwise input won't be recognized

		playerInputListener.up.isActive= CheckActive(playerInputListener.up);
		playerInputListener.up.isDown = CheckDown(playerInputListener.up);

		playerInputListener.left.isActive = CheckActive(playerInputListener.left);
		playerInputListener.left.isDown = CheckDown(playerInputListener.left);

		playerInputListener.down.isActive = CheckActive(playerInputListener.down);
		playerInputListener.down.isDown = CheckDown(playerInputListener.down);

		playerInputListener.right.isActive = CheckActive(playerInputListener.right);
		playerInputListener.right.isDown = CheckDown(playerInputListener.right);
	}
}