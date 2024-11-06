#pragma once

#include "Scene.h"

class MovementControllerSystem
{
private:
	void ManageMovement(Scene& scene, MovementController& movementController, Movement& movement, float deltaTime);
public:
	void Update(Scene& scene, std::vector<MovementController>& controllers, float deltaTime);
};