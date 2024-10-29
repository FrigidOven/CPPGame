#pragma once

#include "Scene.h"
#include "Sprite.h"

#include <vector>
#include <array>

class SpriteSortingSystem
{
public:
	void Update(Scene& scene, std::vector<Sprite>& sprites, std::vector<int>& sortedSpriteIndecies);
};