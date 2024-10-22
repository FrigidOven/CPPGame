#pragma once

#include "ForceBasedMovementController.h"
#include "VelocityBasedMovementController.h"

#include <vector>

class Scene;

class InputSystem
{
private:
	void RemoveUpButtons();
	void AddDownButtons();

	void UpdateForceBasedMovementControllers(Scene* scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers);
	void UpdateVelocityBasedMovementControllers(Scene* scene, std::vector<VelocityBasedMovementController>& velocityBasedMovementControllers);
public:
	std::vector<KeyboardKey> keyboardKeys;
	std::vector<GamepadButton> gamepadButtons;
	std::vector<MouseButton> mouseButtons;

	void Update(Scene* scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers, std::vector<VelocityBasedMovementController>& velocityBasedMovementControllers);
};