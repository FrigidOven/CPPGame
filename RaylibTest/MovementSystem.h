#pragma once

#include "Scene.h"
#include "Controller.h"

#include <vector>

class MovementSystem
{
private:
	void CreateForceBasedMovement(Scene& scene, MovementController& movementController);
	void CreateVelocityBasedMovement(Scene& scene, MovementController& movementController);

public:
	void Update(Scene& scene, std::vector<MovementController>& controllers);
};