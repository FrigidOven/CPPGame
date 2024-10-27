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
	// Sprite systems
	SpriteManagerSystem spriteManagerSystem;
	SpriteRendererSystem spriteRendererSystem;
	
	// Scenes
	Scene currentScene;

public:
	Scene& GetCurrentScene();
	void Update();
};