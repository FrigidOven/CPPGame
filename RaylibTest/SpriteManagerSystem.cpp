#include "SpriteManagerSystem.h"
#include "Sprite.h"
#include "Scene.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void SpriteManagerSystem::Update(Scene& scene, std::vector<SpriteManager>& spriteManagers)
{
	int requiredComponentsMask = 1 << Sprite::ID;

	for (auto& spriteManager : spriteManagers)
	{
		// update orientation and state of sprite manager
		UpdateOrientation(scene, spriteManager);
		UpdateState(scene, spriteManager);

		// procede to update sprite itself
		if ((scene.GetComponentMask(spriteManager.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Sprite& sprite = scene.GetSpriteComponent(spriteManager.entity);
		EntityTag tag = scene.GetTag(spriteManager.entity);

		sprite.sourceRect.y = spriteAtlases[tag]->GetYPos(spriteManager.state, spriteManager.orientation);
		sprite.frameCount = spriteAtlases[tag]->GetFrameCount(spriteManager.state, spriteManager.orientation);
		sprite.fps = spriteAtlases[tag]->GetFPS(spriteManager.state, spriteManager.orientation);

		sprite.currentFrame = Clamp(sprite.currentFrame, 0, sprite.frameCount - 1);
	}
}

/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void SpriteManagerSystem::UpdateState(Scene& scene, SpriteManager& spriteManager)
{
	int entity = spriteManager.entity;

	SpriteState newState;

	if (scene.HasComponent<ForceBasedMovement>(entity) || scene.HasComponent<VelocityBasedMovement>(entity))
		newState = SpriteState::Moving;
	else
		newState = SpriteState::Idle;

	spriteManager.state = newState;
}
void SpriteManagerSystem::UpdateOrientation(Scene& scene, SpriteManager& spriteManager)
{
	int entity = spriteManager.entity;

	SpriteOrientation newOrientation = spriteManager.orientation;
	Vector2 movementDirection = Vector2Zero();

	if (scene.HasComponent<ForceBasedMovement>(entity))
		movementDirection = Vector2Normalize(scene.GetComponent<ForceBasedMovement>(entity).force);
	else if (scene.HasComponent<VelocityBasedMovement>(entity))
		movementDirection = Vector2Normalize(scene.GetComponent<VelocityBasedMovement>(entity).velocity);

	if (Vector2Equals(movementDirection, Vector2{ 0.0f, -1.0f }))
		newOrientation = SpriteOrientation::Up;
	else if (Vector2Equals(movementDirection, Vector2{ -1.0f, 0.0f }))
		newOrientation = SpriteOrientation::Left;
	else if (Vector2Equals(movementDirection, Vector2{ 0.0f, 1.0f }))
		newOrientation = SpriteOrientation::Down;
	else if (Vector2Equals(movementDirection, Vector2{ 1.0f, 0.0f }))
		newOrientation = SpriteOrientation::Right;

	spriteManager.orientation = newOrientation;
}