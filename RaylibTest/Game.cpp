#include "Game.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
Scene& Game::GetCurrentScene()
{
	return currentScene;
}

void Game::Update()
{
	float deltaTime = GetFrameTime();

	// Input Routine:
	inputSystem.Update(&currentScene, currentScene.GetComponents<ForceBasedMovementController>(), currentScene.GetComponents<VelocityBasedMovementController>());
	forceBasedMovementControllerSystem.Update(&currentScene, currentScene.GetComponents<ForceBasedMovementController>());
	velocityBasedMovementControllerSystem.Update(&currentScene, currentScene.GetComponents<VelocityBasedMovementController>());
	// Physics Routine:
	frictionSystem.Update(&currentScene, currentScene.GetComponents<Friction>());
	stoppingForceSystem.Update(&currentScene, currentScene.GetComponents<StoppingForce>());
	forceSystem.Update(&currentScene, currentScene.GetComponents<Force>(), deltaTime);
	accelerationSystem.Update(&currentScene, currentScene.GetComponents<Acceleration>(), deltaTime);
	forceBasedSpeedLimiterSystem.Update(&currentScene, currentScene.GetComponents<ForceBasedSpeedLimiter>());
	velocitySystem.Update(&currentScene, currentScene.GetComponents<Velocity>(), deltaTime);
	// Rendering Routine:
	spriteManagerSystem.Update(&currentScene, currentScene.GetComponents<SpriteManager>());
	spriteRendererSystem.Update(&currentScene, currentScene.GetComponents<BackgroundSprite>(), currentScene.GetComponents<MiddlegroundSprite>(), currentScene.GetComponents<ForegroundSprite>(), deltaTime);
}