#pragma once

#include "Scene.h"

class SpriteSortingSystem
{
public:
	void Update(Scene& scene, std::vector<Sprite>& sprites, std::vector<int>& sortedSpriteIndecies);
};