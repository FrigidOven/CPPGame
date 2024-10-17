#include <vector>
#include "ECS.h"
#include <iostream>

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
	{
		lastPressed = static_cast<KeyboardKey>(GetKeyPressed());
	}

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
	int playerInputComponentsCount = static_cast<int>(playerInputListenerComponents.size());
	for (int i = 0; i < playerInputComponentsCount; i++)
	{
		PlayerInputListener& pil = playerInputListenerComponents[i];

		pil.upIsDown = pil.upKey == lastPressed;
		pil.downIsDown = pil.downKey == lastPressed;
		pil.leftIsDown = pil.leftKey == lastPressed;
		pil.rightIsDown = pil.rightKey == lastPressed;
	}
}