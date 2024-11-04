#include "Game.h"

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
	movementControllerSystem.Update(currentScene, currentScene.GetComponents<MovementController>());
	// Physics Routine:
	movementSystem.Update(currentScene, currentScene.GetComponents<Movement>());
	frictionSystem.Update(currentScene, currentScene.GetComponents<Friction>());
	impulseSystem.Update(currentScene, currentScene.GetComponents<Impulse>(), deltaTime);
	forceApplierSystem.Update(currentScene, currentScene.GetComponents<Rigidbody>(), deltaTime);
	accelerationSystem.Update(currentScene, currentScene.GetComponents<Acceleration>(), deltaTime);
	speedLimiterSystem.Update(currentScene, currentScene.GetComponents<SpeedLimiter>());
	velocitySystem.Update(currentScene, currentScene.GetComponents<Velocity>(), deltaTime);
	// Rendering Routine:
	followCameraSystem.Update(currentScene, currentScene.GetComponents<FollowCamera>());
	spriteManagerSystem.Update(currentScene, currentScene.GetComponents<SpriteManager>());
	spriteSortingSystem.Update(currentScene, currentScene.GetComponents<Sprite>(), currentScene.GetSortedSpriteIndices());
	spriteRendererSystem.Update(currentScene, camera, currentScene.GetComponents<Sprite>(), currentScene.GetSortedSpriteIndices(), deltaTime);
}