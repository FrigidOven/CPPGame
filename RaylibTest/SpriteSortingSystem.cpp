#include "SpriteSortingSystem.h"
#include "Scene.h"

#include <algorithm>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void SpriteSortingSystem::Update(Scene& scene, std::vector<Sprite>& sprites, std::vector<int>& sortedSpriteIndecies)
{
	auto sortingLambda = [this, &scene, &sprites](int index1, int index2) 
	{
			if (sprites[index1].layer != sprites[index2].layer)
				return sprites[index1].layer < sprites[index2].layer;

			if (!scene.HasComponent<Spatial>(sprites[index1].entity))
				return false;
			if (!scene.HasComponent<Spatial>(sprites[index2].entity))
				return true;

			float y1 = scene.GetComponent<Spatial>(sprites[index1].entity).position.y;
			float y2 = scene.GetComponent<Spatial>(sprites[index2].entity).position.y;

			return y1 < y2;
	};

	std::sort(sortedSpriteIndecies.begin(), sortedSpriteIndecies.end(), sortingLambda);
}