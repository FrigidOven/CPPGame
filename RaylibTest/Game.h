#pragma once

// Systems
#include "ControllerSystem.h"
#include "PlayerMovementControllerSystem.h"
#include "MovementControllerSystem.h"
#include "MovementSystem.h"
#include "FrictionSystem.h"
#include "ImpulseSystem.h"
#include "ForceApplierSystem.h"
#include "AccelerationSystem.h"
#include "VelocitySystem.h"
#include "FollowCameraSystem.h"
#include "SpriteManagerSystem.h"
#include "SpriteSortingSystem.h"
#include "SpriteRendererSystem.h"

class Game
{
private:
	// Input routine systems
	ControllerSystem controllerSystem;
	PlayerMovementControllerSystem playerMovementControllerSystem;
	MovementControllerSystem movementControllerSystem;
	// Physics routine systems
	MovementSystem movementSystem;
	FrictionSystem frictionSystem;
	ImpulseSystem impulseSystem;
	ForceApplierSystem forceApplierSystem;
	AccelerationSystem accelerationSystem;
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