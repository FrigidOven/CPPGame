#pragma once

#include "Scene.h"
#include "Controller.h"

#include <vector>

class MovementControllerSystem
{
private:
	void HandleForceBasedMovement(Scene& scene, MovementController& movementController);
	void HandleVelocityBasedMovement(Scene& scene, MovementController& movementController);

public:
	void Update(Scene& scene, std::vector<MovementController>& controllers);
};