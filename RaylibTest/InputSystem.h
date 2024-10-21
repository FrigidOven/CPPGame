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
	void Update(Scene* scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers, std::vector<VelocityBasedMovementController>& velocityBasedMovementControllers);
};