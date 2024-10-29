#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/

int Scene::CreateEntity(EntityTag tag)
{
	entities.emplace_back
	(
		static_cast<int>(entities.size()),	// id
		tag,
		0															// component mask
	);

	// reserve space for all components even if the entity wont use them all
	int componentCount = static_cast<int>(Component::COMPONENT_COUNT);
	components.resize(components.size() + componentCount, -1);

	return static_cast<int>(entities.size()) - 1;
}

std::vector<int>& Scene::GetSortedSpriteIndices()
{
	return sortedSpriteIndices;
}

int Scene::GetComponentMask(int entityId)
{
	return entities[entityId].componentMask;
}

EntityTag Scene::GetTag(int entityId)
{
	return entities[entityId].tag;
}
