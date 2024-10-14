#include <vector>
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
SpriteRendererSystem::SpriteRendererSystem(Scene& scene, std::vector<Sprite>& spriteComponents)
	: scene(scene), spriteComponents(spriteComponents)
{
}
void SpriteRendererSystem::Draw()
{
	ClearBackground(BLACK);
	BeginDrawing();

	int spriteCount = static_cast<int>(spriteComponents.size());

	Rectangle dest{ 0, 0, 0, 0 };
	Rectangle source{ 0, 0, 0, 0 };

	for (int i = 0; i < spriteCount; i++)
	{
		Sprite& sprite = spriteComponents[i];

		Vector2 position = scene.GetSpatialComponent(sprite.entity).position;
		float rotation = scene.GetSpatialComponent(sprite.entity).rotation;
		
		dest.x = position.x;
		dest.y = position.y;
		dest.width = sprite.width;
		dest.height = sprite.height;

		// draw sprites centered at destination
		Vector2 origin = { dest.width / 2, dest.height / 2 };

		DrawTexturePro(*sprite.source, sprite.sourceRect, dest, origin, rotation, WHITE);

		// only update sprites if they have multiple frames
		if(sprite.frameCount > 1)
			UpdateSprite(sprite);
	}

	EndDrawing();
}

/*
===================================================================================================
 Private Functions
===================================================================================================
*/

void SpriteRendererSystem::UpdateSprite(Sprite& sprite)
{
	sprite.timer += GetFrameTime();
	
	if (sprite.timer >= 1 / sprite.fps)
	{
		sprite.timer = 0;

		int nextX = static_cast<int>(sprite.sourceRect.x + sprite.sourceRect.width);
		int maxX = static_cast<int>(sprite.sourceRect.width * sprite.frameCount);

		sprite.sourceRect.x = nextX % maxX;
	}
}