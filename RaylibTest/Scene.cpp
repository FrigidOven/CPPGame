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

bool Scene::AddSpriteComponent(int entityId, int layer, Texture2D* source, Rectangle sourceRect, float destWidth, float destHeight, int frameCount, int currentFrame, float fps)
{
	bool successful = !HasComponent<Sprite>(entityId);

	if (successful)
	{
		entities[entityId].componentMask |= 1 << Sprite::ID;
		std::vector<Sprite>* componentList = static_cast<std::vector<Sprite>*>(componentLists[Sprite::ID]);
		sortedSpriteIndecies.push_back(static_cast<int>(componentList->size()));
		componentList->emplace_back(entityId, layer, source, sourceRect, destWidth, destHeight, frameCount, currentFrame, fps);
		components[entityId * Component::COMPONENT_COUNT + Sprite::ID] = static_cast<int>(componentList->size()) - 1;
	}

	return successful;
}
bool Scene::RemoveSpriteComponent(int entityId)
{
	return false;
}

std::vector<int>& Scene::GetSortedSpriteIndecies()
{
	return sortedSpriteIndecies;
}

int Scene::GetComponentMask(int entityId)
{
	return entities[entityId].componentMask;
}

EntityTag Scene::GetTag(int entityId)
{
	return entities[entityId].tag;
}
