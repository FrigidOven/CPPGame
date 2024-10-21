#include "InputSystem.h"
#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void InputSystem::Update(Scene* scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers, std::vector<VelocityBasedMovementController>& velocityBasedMovementControllers)
{
	RemoveUpButtons();
	AddDownButtons();

	UpdateForceBasedMovementControllers(scene, forceBasedMovementControllers);
	UpdateVelocityBasedMovementControllers(scene, velocityBasedMovementControllers);
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

void InputSystem::UpdateForceBasedMovementControllers(Scene* scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers)
{
	for (auto& forceBasedMovementController : forceBasedMovementControllers)
	{
		// update the input listener
		forceBasedMovementController.inputListener.Update(this);

		// use input listener to update inputs
		// check active before checking down, otherwise input won't be recognized
		forceBasedMovementController.up.isActive = forceBasedMovementController.inputListener.CheckActive(forceBasedMovementController.up);
		forceBasedMovementController.up.isDown = forceBasedMovementController.inputListener.CheckDown(forceBasedMovementController.up);

		forceBasedMovementController.left.isActive = forceBasedMovementController.inputListener.CheckActive(forceBasedMovementController.left);
		forceBasedMovementController.left.isDown = forceBasedMovementController.inputListener.CheckDown(forceBasedMovementController.left);

		forceBasedMovementController.down.isActive = forceBasedMovementController.inputListener.CheckActive(forceBasedMovementController.down);
		forceBasedMovementController.down.isDown = forceBasedMovementController.inputListener.CheckDown(forceBasedMovementController.down);

		forceBasedMovementController.right.isActive = forceBasedMovementController.inputListener.CheckActive(forceBasedMovementController.right);
		forceBasedMovementController.right.isDown = forceBasedMovementController.inputListener.CheckDown(forceBasedMovementController.right);
	}
}
void InputSystem::UpdateVelocityBasedMovementControllers(Scene* scene, std::vector<VelocityBasedMovementController>& velocityBasedMovementControllers)
{
	for (auto& velocityBasedMovementController : velocityBasedMovementControllers)
	{
		velocityBasedMovementController.inputListener.Update(this);

		velocityBasedMovementController.up.isActive = velocityBasedMovementController.inputListener.CheckActive(velocityBasedMovementController.up);
		velocityBasedMovementController.up.isDown = velocityBasedMovementController.inputListener.CheckDown(velocityBasedMovementController.up);

		velocityBasedMovementController.left.isActive = velocityBasedMovementController.inputListener.CheckActive(velocityBasedMovementController.left);
		velocityBasedMovementController.left.isDown = velocityBasedMovementController.inputListener.CheckDown(velocityBasedMovementController.left);

		velocityBasedMovementController.down.isActive = velocityBasedMovementController.inputListener.CheckActive(velocityBasedMovementController.down);
		velocityBasedMovementController.down.isDown = velocityBasedMovementController.inputListener.CheckDown(velocityBasedMovementController.down);

		velocityBasedMovementController.right.isActive = velocityBasedMovementController.inputListener.CheckActive(velocityBasedMovementController.right);
		velocityBasedMovementController.right.isDown = velocityBasedMovementController.inputListener.CheckDown(velocityBasedMovementController.right);
	}
}