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
	int requiredComponentsMask = (1 << Sprite::ID) | (1 << Direction::ID);

	for (auto& spriteManager : spriteManagers)
	{
		if ((scene.GetComponentMask(spriteManager.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		// update orientation and state of sprite manager
		UpdateState(scene, spriteManager);

		// procede to update sprite itself
		Sprite& sprite = scene.GetComponent<Sprite>(spriteManager.entity);
		Orientation orientation = scene.GetComponent<Direction>(spriteManager.entity).direction;
		EntityTag tag = scene.GetTag(spriteManager.entity);

		float oldY = sprite.sourceRect.y;

		sprite.sourceRect.y = spriteAtlases[tag]->GetYPos(spriteManager.state, orientation);
		sprite.frameCount = spriteAtlases[tag]->GetFrameCount(spriteManager.state, orientation);
		sprite.fps = spriteAtlases[tag]->GetFPS(spriteManager.state, orientation);

		bool spriteChanged = oldY != sprite.sourceRect.y;

		if (spriteChanged)
			sprite.currentFrame = 0;
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