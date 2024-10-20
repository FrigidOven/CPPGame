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

bool InputSystem::CheckInput(Input input)
{
	switch (input.controlType)
	{
	case Keyboard:
		return keyboardKeys.size() > 0 && keyboardKeys.back() == input.controlValue;
	}
}


void InputSystem::UpdatePlayerInputListeners(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents)
{
	for (auto& playerInputListener : playerInputListenerComponents)
	{
		playerInputListener.up.isActive= CheckInput(playerInputListener.up);
		playerInputListener.left.isActive = CheckInput(playerInputListener.left);
		playerInputListener.down.isActive = CheckInput(playerInputListener.down);
		playerInputListener.right.isActive = CheckInput(playerInputListener.right);
	}
}