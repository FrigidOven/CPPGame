#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
InputSystem::InputSystem(InputMode inputMode)
	: inputMode(inputMode)
	, lastPressed(KEY_NULL)
{
}
void InputSystem::Update(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents)
{
	if (!IsKeyDown(lastPressed))
		lastPressed = static_cast<KeyboardKey>(GetKeyPressed());

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
void InputSystem::UpdatePlayerInputListeners(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents)
{
	for (auto& playerInputListener : playerInputListenerComponents)
	{
		playerInputListener.upIsDown = playerInputListener.upKey == lastPressed;
		playerInputListener.downIsDown = playerInputListener.downKey == lastPressed;
		playerInputListener.leftIsDown = playerInputListener.leftKey == lastPressed;
		playerInputListener.rightIsDown = playerInputListener.rightKey == lastPressed;
	}
}