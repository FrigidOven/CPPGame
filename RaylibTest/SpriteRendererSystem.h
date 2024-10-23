#pragma once

#include "BackgroundSprite.h"
#include "MiddlegroundSprite.h"
#include "ForegroundSprite.h"

#include <vector>

class Scene;

class SpriteRendererSystem
{
private:
	void UpdateBackgroundSprite(BackgroundSprite& backgroundSprite, float deltaTime);
	void UpdateMiddlegroundSprite(MiddlegroundSprite& middlegroundSprite, float deltaTime);
	void UpdateForegroundSprite(ForegroundSprite& foregroundSprite, float deltaTime);

public:
	void Update(Scene* scene, std::vector<BackgroundSprite>& backgroundSprites, std::vector<MiddlegroundSprite>& middlegroundSprites, std::vector<ForegroundSprite>& foregroundSprites, float deltaTime);
};