#include "Game.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
Game::Game()
{
	camera.zoom = 3.0f;
}
Scene& Game::GetCurrentScene()
{
	return currentScene;
}

void Game::Update()
{
	UpdateCameraZoom();
	float deltaTime = GetFrameTime();

	// Input Routine:
	controllerSystem.Update(currentScene, currentScene.GetComponents<Controller>());
	playerMovementControllerSystem.Update(currentScene, currentScene.GetComponents<Controller>());
	// Physics Routine:
	frictionSystem.Update(currentScene, currentScene.GetComponents<Friction>());
	movementControllerSystem.Update(currentScene, currentScene.GetComponents<MovementController>(), deltaTime);
	movementSystem.Update(currentScene, currentScene.GetComponents<Movement>());
	impulseSystem.Update(currentScene, currentScene.GetComponents<Impulse>(), deltaTime);
	forceApplierSystem.Update(currentScene, currentScene.GetComponents<Rigidbody>(), deltaTime);
	accelerationSystem.Update(currentScene, currentScene.GetComponents<Acceleration>(), deltaTime);
	velocitySystem.Update(currentScene, currentScene.GetComponents<Velocity>(), deltaTime);
	// Rendering Routine:
	followCameraSystem.Update(currentScene, currentScene.GetComponents<FollowCamera>());
	spriteManagerSystem.Update(currentScene, currentScene.GetComponents<SpriteManager>());
	spriteSortingSystem.Update(currentScene, currentScene.GetComponents<Sprite>(), currentScene.GetSortedSpriteIndices());
	spriteRendererSystem.Update(currentScene, camera, currentScene.GetComponents<Sprite>(), currentScene.GetSortedSpriteIndices(), deltaTime);
}
/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void Game::UpdateCameraZoom()
{
	camera.zoom = static_cast<float>(PIXEL_SIZE) * static_cast<float>(GetScreenHeight()) / static_cast<float>(DEFAULT_WINDOW_HEIGHT);
}