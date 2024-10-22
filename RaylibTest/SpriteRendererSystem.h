#pragma once

#include "BackgroundSprite.h"
#include "MiddlegroundSprite.h"
#include "ForegroundSprite.h"

#include <vector>

class Scene;

class SpriteRendererSystem
{
private:
	void UpdateBackgroundSprite(BackgroundSprite& backgroundSprite);
	void UpdateMiddlegroundSprite(MiddlegroundSprite& middlegroundSprite);
	void UpdateForegroundSprite(ForegroundSprite& foregroundSprite);

public:
	void Update(Scene* scene, std::vector<BackgroundSprite>& backgroundSprites, std::vector<MiddlegroundSprite>& middlegroundSprites, std::vector<ForegroundSprite>& foregroundSprites);
};