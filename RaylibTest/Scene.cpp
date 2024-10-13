#include <vector>
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
/*
=================================================
 General
=================================================
*/
Scene::Scene()
	:nextEntityId(0), spriteRendererSystem(new SpriteRendererSystem(*this, spriteComponents))
{
}
int Scene::CreateEntity()
{
	entities.emplace_back
	(
		static_cast<int>(entities.size()),	// id
		0									// component mask
	);

	// reserve space for all components even if the entity wont use them all
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	components.resize(components.size() + componentCount, -1);

	return static_cast<int>(entities.size()) - 1;
}
void Scene::Update()
{
	spriteRendererSystem->Draw();
}
/*
=================================================
 Add Components
=================================================
*/
bool Scene::AddSpatialComponent(int entityId, Vector2 position, float rotation)
{
	bool successful = AddComponent<Spatial>(entityId, ComponentType::Position, spatialComponents);

	if (!successful)
		return !successful;

	spatialComponents.emplace_back
	(
		entityId,
		position,
		rotation
	);

	return successful;
}
bool Scene::AddSpriteComponent(int entityId, Texture2D* texture, Rectangle sourceRect, float width, float height, int frameCount, float fps)
{
	bool successful = AddComponent<Sprite>(entityId, ComponentType::Sprite, spriteComponents);

	if (!successful)
		return !successful;

	spriteComponents.emplace_back
	(
		entityId,
		texture,
		sourceRect,
		width,
		height,
		frameCount,
		0.0,		// timer
		fps						
	);

	return successful;
}

/*
=================================================
 Get Components
=================================================
*/

Spatial& Scene::GetSpatialComponent(int entityId)
{
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Position)];

	return spatialComponents[index];
}
Sprite& Scene::GetSpriteComponent(int entityId)
{
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Sprite)];

	return spriteComponents[index];
}

/*
=================================================
 Remove Component
=================================================
*/

bool Scene::RemoveComponent(int entityId, ComponentType componentType)
{
	int componentId = static_cast<int>(componentType);
	
	// entity does not have component of type componentType
	if ((entities[entityId].componentMask & componentId) == 0)
		return false;

	entities[entityId].componentMask &= ~componentId;

	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(componentType)];

	// TODO: Implment a freelist or some way of not moving indecies when component is removed.
	return true;
}

/*
===================================================================================================
 Private Functions
===================================================================================================
*/

template<typename T>
bool Scene::AddComponent(int entityId, ComponentType componentType, std::vector<T>& componentList)
{
	int componentId = static_cast<int>(componentType);
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);

	// entity already component of type componentType
	if ((entities[entityId].componentMask & componentId) != 0)
		return false;

	entities[entityId].componentMask |= componentId;

	components[entityId * componentCount + ComponentIdOffset(componentType)] = static_cast<int>(componentList.size());
	return true;
}


int Scene::ComponentIdOffset(ComponentType componentType)
{
	int componentId = static_cast<int>(componentType);

	// find log2(componentId)

	int componentIdOffset = 0;
	for (componentIdOffset = 0; (componentId & 1) == 0; componentIdOffset++)
	{
		componentId >>= 1;
	}
	return componentIdOffset;
}
