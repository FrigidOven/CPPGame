#pragma once

#include "Systems.h"
#include "Scene.h"
#include "TextureManager.h"

class Game
{
private:
	// Resource managers
	TextureManager textureManager;

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
	SpriteSortingSystem spriteSortingSystem;
	SpriteRendererSystem spriteRendererSystem;
	
	// Scenes
	Scene currentScene;

public:
	Scene& GetCurrentScene();
	void Update();
};