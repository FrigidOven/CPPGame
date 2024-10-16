#include <vector>
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void InputSystem::Update(Scene* scene, std::vector<PlayerInputListener> playerInputListenerComponents)
{
	if(!IsKeyPressed(lastPressed))
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
void InputSystem::UpdatePlayerInputListeners(Scene* scene, std::vector<PlayerInputListener> playerInputListenerComponents)
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