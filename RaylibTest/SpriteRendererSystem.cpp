#include "SpriteRendererSystem.h"
#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void SpriteRendererSystem::Update(Scene* scene, std::vector<BackgroundSprite>& backgroundSprites, std::vector<MiddlegroundSprite>& middlegroundSprites, std::vector<ForegroundSprite>& foregroundSprites)
{
	ClearBackground(BLACK);
	BeginDrawing();

	Rectangle dest{ 0, 0, 0, 0 };
	Rectangle source{ 0, 0, 0, 0 };

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------
	// BACKGROUND SPRITES
	for (auto& backgroundSprite : backgroundSprites)
	{
		Vector2 position = scene->GetComponent<Spatial>(backgroundSprite.entity).position;
		float rotation = scene->GetComponent<Spatial>(backgroundSprite.entity).rotation;

		dest.x = position.x;
		dest.y = position.y;
		dest.width = backgroundSprite.destWidth;
		dest.height = backgroundSprite.destHeight;

		// assume frames are layed out horizontally
		source.x = backgroundSprite.sourceRect.x + backgroundSprite.currentFrame * backgroundSprite.sourceRect.width;
		source.y = backgroundSprite.sourceRect.y;
		source.width = backgroundSprite.sourceRect.width;
		source.height = backgroundSprite.sourceRect.height;

		// draw sprites centered at destination
		Vector2 origin = { dest.width / 2, dest.height / 2 };

		DrawTexturePro(*backgroundSprite.source, source, dest, origin, rotation, WHITE);

		// only update sprites if they have multiple frames
		if (backgroundSprite.frameCount > 1)
			UpdateBackgroundSprite(backgroundSprite);
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------
	// MIDDLEGROUND SPRITES
	for (auto& middlegroundSprite : middlegroundSprites)
	{
		Vector2 position = scene->GetComponent<Spatial>(middlegroundSprite.entity).position;
		float rotation = scene->GetComponent<Spatial>(middlegroundSprite.entity).rotation;

		dest.x = position.x;
		dest.y = position.y;
		dest.width = middlegroundSprite.destWidth;
		dest.height = middlegroundSprite.destHeight;

		source.x = middlegroundSprite.sourceRect.x + middlegroundSprite.currentFrame * middlegroundSprite.sourceRect.width;
		source.y = middlegroundSprite.sourceRect.y;
		source.width = middlegroundSprite.sourceRect.width;
		source.height = middlegroundSprite.sourceRect.height;

		Vector2 origin = { dest.width / 2, dest.height / 2 };

		DrawTexturePro(*middlegroundSprite.source, source, dest, origin, rotation, WHITE);

		if (middlegroundSprite.frameCount > 1)
			UpdateMiddlegroundSprite(middlegroundSprite);
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------
    // FOREGROUND SPRITES
	for (auto& foregroundSprite : foregroundSprites)
	{
		Vector2 position = scene->GetComponent<Spatial>(foregroundSprite.entity).position;
		float rotation = scene->GetComponent<Spatial>(foregroundSprite.entity).rotation;

		dest.x = position.x;
		dest.y = position.y;
		dest.width = foregroundSprite.destWidth;
		dest.height = foregroundSprite.destHeight;

		source.x = foregroundSprite.sourceRect.x + foregroundSprite.currentFrame * foregroundSprite.sourceRect.width;
		source.y = foregroundSprite.sourceRect.y;
		source.width = foregroundSprite.sourceRect.width;
		source.height = foregroundSprite.sourceRect.height;

		Vector2 origin = { dest.width / 2, dest.height / 2 };

		DrawTexturePro(*foregroundSprite.source, source, dest, origin, rotation, WHITE);

		if (foregroundSprite.frameCount > 1)
			UpdateForegroundSprite(foregroundSprite);
	}

	EndDrawing();
}

/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void SpriteRendererSystem::UpdateBackgroundSprite(BackgroundSprite& backgroundSprite)
{
	backgroundSprite.timer += GetFrameTime();

	if (backgroundSprite.timer >= 1.0f / backgroundSprite.fps)
	{
		backgroundSprite.timer = 0;
		backgroundSprite.currentFrame = (backgroundSprite.currentFrame + 1) % (backgroundSprite.frameCount);
	}
}
void SpriteRendererSystem::UpdateMiddlegroundSprite(MiddlegroundSprite& middlegroundSprite)
{
	middlegroundSprite.timer += GetFrameTime();

	if (middlegroundSprite.timer >= 1.0f / middlegroundSprite.fps)
	{
		middlegroundSprite.timer = 0;
		middlegroundSprite.currentFrame = (middlegroundSprite.currentFrame + 1) % (middlegroundSprite.frameCount);
	}
}
void SpriteRendererSystem::UpdateForegroundSprite(ForegroundSprite& foregroundSprite)
{
	foregroundSprite.timer += GetFrameTime();

	if (foregroundSprite.timer >= 1.0f / foregroundSprite.fps)
	{
		foregroundSprite.timer = 0;
		foregroundSprite.currentFrame = (foregroundSprite.currentFrame + 1) % (foregroundSprite.frameCount);
	}
}