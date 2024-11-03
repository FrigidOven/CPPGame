#include "Game.h"
#include "GameConstants.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
Game::Game()
{
	camera.offset = Vector2((float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f);
	camera.zoom = 1.0f;
}
Scene& Game::GetCurrentScene()
{
	return currentScene;
}

void Game::Update()
{
	float deltaTime = GetFrameTime();

	// Input Routine:
	controllerSystem.Update(currentScene, currentScene.GetComponents<Controller>());
	playerMovementControllerSystem.Update(currentScene, currentScene.GetComponents<Controller>());
	// Physics/Movement Routines:
	movementControllerSystem.Update(currentScene, currentScene.GetComponents<MovementController>());
	movementSystem.Update(currentScene, currentScene.GetComponents<Movement>());
	frictionSystem.Update(currentScene, currentScene.GetComponents<Friction>());
	stoppingForceSystem.Update(currentScene, currentScene.GetComponents<StoppingForce>());
	impulseSystem.Update(currentScene, currentScene.GetComponents<Impulse>(), deltaTime);
	forceApplierSystem.Update(currentScene, currentScene.GetComponents<ForceReceiver>(), deltaTime);
	accelerationSystem.Update(currentScene, currentScene.GetComponents<Acceleration>(), deltaTime);
	speedLimiterSystem.Update(currentScene, currentScene.GetComponents<SpeedLimiter>());
	velocitySystem.Update(currentScene, currentScene.GetComponents<Velocity>(), deltaTime);
	// Rendering Routine:
	followCameraSystem.Update(currentScene, currentScene.GetComponents<FollowCamera>());
	spriteManagerSystem.Update(currentScene, currentScene.GetComponents<SpriteManager>());
	spriteSortingSystem.Update(currentScene, currentScene.GetComponents<Sprite>(), currentScene.GetSortedSpriteIndices());
	spriteRendererSystem.Update(currentScene, camera, currentScene.GetComponents<Sprite>(), currentScene.GetSortedSpriteIndices(), deltaTime);
}