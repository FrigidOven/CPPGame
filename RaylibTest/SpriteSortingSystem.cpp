#include "SpriteSortingSystem.h"
#include "Scene.h"

#include <algorithm>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void SpriteSortingSystem::Update(Scene& scene, std::vector<Sprite>& sprites, std::vector<int>& sortedSpriteIndices)
{
	while (sortedSpriteIndices.size() < sprites.size())
		sortedSpriteIndices.push_back(static_cast<int>(sortedSpriteIndices.size()));

	int maxIndex = static_cast<int>(sprites.size()) - 1;

	auto sortingLambda = [this, &scene, &sprites, &maxIndex](int index1, int index2) 
	{
			if (index1 > maxIndex || index2 > maxIndex)
				return index1 <= maxIndex;

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

	std::sort(sortedSpriteIndices.begin(), sortedSpriteIndices.end(), sortingLambda);

	while (sortedSpriteIndices.size() > sprites.size())
		sortedSpriteIndices.pop_back();
}