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
		std::vector<Sprite>& componentList = sprites[layer];
		componentList.emplace_back(entityId, source, sourceRect, destWidth, destHeight, frameCount, currentFrame, fps);

		// the first four bits of the entry in "components" will be used to store the layer,
		// the last 28 bits will be used to store the actual index into the list at that layer.
		int layerMask = layer << 28;
		int indexMask = (static_cast<int>(componentList.size()) - 1) & (0x0FFF);
		int location = layerMask | indexMask;

		components[entityId * Component::COMPONENT_COUNT + Sprite::ID] = location;
	}

	return successful;
}

bool Scene::RemoveSpriteComponent(int entityId)
{
	bool successful = HasComponent<Sprite>(entityId);

	if (successful)
	{
		int layerAndIndex = components[entityId * Component::COMPONENT_COUNT + Sprite::ID];
		int layer = (layerAndIndex >> 28) & 0x000F;
		int index = layerAndIndex & 0x0FFF;
		std::vector<Sprite>& componentList = sprites[layer];

		// swap and pop approach to keep vectors tightly packed
		if (index < componentList.size())
		{
			Sprite toRemove = componentList[index];
			Sprite back = componentList.back();

			componentList[componentList.size() - 1] = toRemove;
			componentList[index] = back;

			components[back.entity * Component::COMPONENT_COUNT + Sprite::ID] = index;
		}

		components[entityId * Component::COMPONENT_COUNT + Sprite::ID] = -1;
		componentList.pop_back();

		entities[entityId].componentMask &= ~(1 << Sprite::ID);
	}

	return successful;
}

Sprite& Scene::GetSpriteComponent(int entityId)
{
	int layerAndIndex = components[entityId * Component::COMPONENT_COUNT + Sprite::ID];
	int layer = (layerAndIndex >> 28) & 0x000F;
	int index = layerAndIndex & 0x0FFF;
	return sprites[layer][index];
}

std::array<std::vector<Sprite>, 16>& Scene::GetSpriteComponents()
{
	return sprites;
}

int Scene::GetComponentMask(int entityId)
{
	return entities[entityId].componentMask;
}

EntityTag Scene::GetTag(int entityId)
{
	return entities[entityId].tag;
}
