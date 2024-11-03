#pragma once

#include "Systems.h"
#include "Scene.h"

class Game
{
private:
	// Input routine systems
	ControllerSystem controllerSystem;
	PlayerMovementControllerSystem playerMovementControllerSystem;
	// Physics / Movement routines systems
	MovementControllerSystem movementControllerSystem;
	MovementSystem movementSystem;
	FrictionSystem frictionSystem;
	StoppingForceSystem stoppingForceSystem;
	ImpulseSystem impulseSystem;
	ForceApplierSystem forceApplierSystem;
	AccelerationSystem accelerationSystem;
	SpeedLimiterSystem speedLimiterSystem;
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