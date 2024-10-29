#include "SpriteRendererSystem.h"
#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void SpriteRendererSystem::Update(Scene& scene, std::vector<Sprite>& sprites, std::vector<int>& sortedSpriteIndecies, float deltaTime)
{
	ClearBackground(BLACK);
	BeginDrawing();

	Rectangle dest{ 0, 0, 0, 0 };
	Rectangle source{ 0, 0, 0, 0 };

	int requiredComponentsMask = 1 << Spatial::ID;

	for (auto& index : sortedSpriteIndecies)
	{
		Sprite& sprite = sprites[index];

		if ((scene.GetComponentMask(sprite.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Vector2 position = scene.GetComponent<Spatial>(sprite.entity).position;
		float rotation = scene.GetComponent<Spatial>(sprite.entity).rotation;

		dest.x = position.x;
		dest.y = position.y;
		dest.width = sprite.destWidth;
		dest.height = sprite.destHeight;

		// assume frames are layed out horizontally
		source.x = sprite.sourceRect.x + sprite.currentFrame * sprite.sourceRect.width;
		source.y = sprite.sourceRect.y;
		source.width = sprite.sourceRect.width;
		source.height = sprite.sourceRect.height;

		// draw sprites centered at destination
		Vector2 origin = { dest.width / 2, dest.height / 2 };

		DrawTexturePro(*sprite.source, source, dest, origin, rotation, WHITE);

		// only update sprites if they have multiple frames
		if (sprite.frameCount > 1)
			UpdateSprite(sprite, deltaTime);
	}

	EndDrawing();
}

/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void SpriteRendererSystem::UpdateSprite(Sprite& sprite, float deltaTime)
{
	sprite.timer += deltaTime;

	if (sprite.timer >= 1.0f / sprite.fps)
	{
		sprite.timer = 0;
		sprite.currentFrame = (sprite.currentFrame + 1) % (sprite.frameCount);
	}
}