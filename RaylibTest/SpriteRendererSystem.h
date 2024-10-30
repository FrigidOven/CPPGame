#pragma once

#include "Scene.h"
#include "Sprite.h"

#include <vector>

class SpriteRendererSystem
{
private:
	void UpdateSprite(Sprite& sprite, float deltaTime);

public:
	void Update(Scene& scene, Camera2D& camera, std::vector<Sprite>& sprites, std::vector<int>& sortedSpriteIndecies, float deltaTime);
};