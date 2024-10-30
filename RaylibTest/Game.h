#pragma once

#include "Systems.h"
#include "Scene.h"

class Game
{
private:
	// Input routine systems
	InputSystem inputSystem;
	ForceBasedMovementControllerSystem forceBasedMovementControllerSystem;
	VelocityBasedMovementControllerSystem velocityBasedMovementControllerSystem;
	// Physics / Movement routines systems
	FrictionSystem frictionSystem;
	StoppingForceSystem stoppingForceSystem;
	ForceSystem forceSystem;
	AccelerationSystem accelerationSystem;
	ForceBasedSpeedLimiterSystem forceBasedSpeedLimiterSystem;
	VelocitySystem velocitySystem;
	// Rendering systems
	FollowCameraSystem followCameraSystem;
	SpriteManagerSystem spriteManagerSystem;
	SpriteSortingSystem spriteSortingSystem;
	SpriteRendererSystem spriteRendererSystem;

	// camera
	Camera2D camera;

	// Scenes
	Scene currentScene{ &camera };

public:
	Game();
	Scene& GetCurrentScene();
	void Update();
};