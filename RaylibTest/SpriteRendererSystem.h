#pragma once

#include "Scene.h"
#include "Sprite.h"

#include <vector>

class SpriteRendererSystem
{
private:
	void UpdateSprite(Sprite& sprite, float deltaTime);

public:
	void Update(Scene& scene, std::vector<Sprite>& sprites, std::vector<int>& sortedSpriteIndecies, float deltaTime);
};