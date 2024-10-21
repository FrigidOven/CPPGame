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
	RemoveUpButtons();
	AddDownButtons();

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

void InputSystem::RemoveUpButtons()
{
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
void InputSystem::AddDownButtons()
{
	// adding down keyboard keys
	KeyboardKey key = KEY_NULL;
	do
	{
		key = static_cast<KeyboardKey>(GetKeyPressed());
		if (key != KEY_NULL &&
			std::find(keyboardKeys.begin(), keyboardKeys.end(), key) == keyboardKeys.end())
			keyboardKeys.push_back(key);

	} while (key != KEY_NULL);

	// TODO: add down gamepad buttons

	// TODO: add down mouse buttons
}

void InputSystem::UpdatePlayerInputListeners(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents)
{
	for (auto& playerInputListener : playerInputListenerComponents)
	{
		// update the input listener
		playerInputListener.inputListener.Update(this);

		// use input listener to update inputs
		// check active before checking down, otherwise input won't be recognized
		playerInputListener.up.isActive= playerInputListener.inputListener.CheckActive(playerInputListener.up);
		playerInputListener.up.isDown = playerInputListener.inputListener.CheckDown(playerInputListener.up);

		playerInputListener.left.isActive = playerInputListener.inputListener.CheckActive(playerInputListener.left);
		playerInputListener.left.isDown = playerInputListener.inputListener.CheckDown(playerInputListener.left);

		playerInputListener.down.isActive = playerInputListener.inputListener.CheckActive(playerInputListener.down);
		playerInputListener.down.isDown = playerInputListener.inputListener.CheckDown(playerInputListener.down);

		playerInputListener.right.isActive = playerInputListener.inputListener.CheckActive(playerInputListener.right);
		playerInputListener.right.isDown = playerInputListener.inputListener.CheckDown(playerInputListener.right);
	}
}