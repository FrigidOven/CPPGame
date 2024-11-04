#include "SpriteManagerSystem.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void SpriteManagerSystem::Update(Scene& scene, std::vector<SpriteManager>& spriteManagers)
{
	int requiredComponentsMask = (1 << static_cast<int>(Sprite::ID));

	for (auto& spriteManager : spriteManagers)
	{
		if ((scene.GetComponentMask(spriteManager.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Sprite& sprite = scene.GetComponent<Sprite>(spriteManager.entity);
		Tag& tag = scene.GetComponent<Tag>(spriteManager.entity);

		float oldY = sprite.sourceRect.y;

		sprite.sourceRect.y = spriteAtlases[tag.entityType]->GetYPos(tag.state, tag.direction);
		sprite.frameCount = spriteAtlases[tag.entityType]->GetFrameCount(tag.state, tag.direction);
		sprite.fps = spriteAtlases[tag.entityType]->GetFPS(tag.state, tag.direction);

		bool spriteChanged = oldY != sprite.sourceRect.y;

		if (spriteChanged)
		{
			sprite.currentFrame = 0;
			sprite.timer = 0.0f;
		}
	}
}