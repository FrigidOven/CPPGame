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
	: spriteRendererSystem(new SpriteRendererSystem(*this, spriteComponents))
	, velocitySystem(new VelocitySystem(*this, velocityComponents))
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
	velocitySystem->Update();
}
/*
=================================================
 Add Components
=================================================
*/
bool Scene::AddSpatialComponent(int entityId, Vector2 position, float rotation)
{
	bool successful = AddComponent<Spatial>(entityId, ComponentType::Spatial, spatialComponents);

	if (!successful)
		return successful;

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
		return successful;

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
bool Scene::AddVelocityComponent(int entityId, Vector2 velocity, float angularVelocity)
{
	bool successful = AddComponent<Velocity>(entityId, ComponentType::Velocity, velocityComponents);

	if (!successful)
		return successful;

	velocityComponents.emplace_back
	(
		entityId,
		velocity,
		angularVelocity
	);

	return successful;
}
/*
=================================================
 Remove Components
=================================================
*/

bool Scene::RemoveSpatialComponent(int entityId)
{
	// entity does not have component of type componentType
	if (!HasComponent(entityId, ComponentType::Spatial))
		return false;

	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Spatial)];

	// swap and pop approach to keep vectors tightly packed
	if (index < spatialComponents.size())
	{
		Spatial toRemove = spatialComponents[index];
		Spatial back = spatialComponents.back();

		spatialComponents[spatialComponents.size() - 1] = toRemove;
		spatialComponents[index] = back;

		components[back.entity * componentCount + ComponentIdOffset(ComponentType::Spatial)] = index;
	}

	components[entityId * componentCount + ComponentIdOffset(ComponentType::Spatial)] = -1;
	spatialComponents.pop_back();

	int componentId = static_cast<int>(ComponentType::Spatial);
	entities[entityId].componentMask &= ~componentId;

	return true;
}
bool Scene::RemoveSpriteComponent(int entityId)
{
	// entity does not have component of type componentType
	if (!HasComponent(entityId, ComponentType::Sprite))
		return false;

	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Sprite)];

	// swap and pop approach to keep vectors tightly packed
	if (index < spriteComponents.size())
	{
		Sprite toRemove = spriteComponents[index];
		Sprite back = spriteComponents.back();

		spriteComponents[spriteComponents.size() - 1] = toRemove;
		spriteComponents[index] = back;

		components[back.entity * componentCount + ComponentIdOffset(ComponentType::Sprite)] = index;
	}

	components[entityId * componentCount + ComponentIdOffset(ComponentType::Sprite)] = -1;
	spriteComponents.pop_back();

	int componentId = static_cast<int>(ComponentType::Sprite);
	entities[entityId].componentMask &= ~componentId;

	return true;
}
bool Scene::RemoveVelocityComponent(int entityId)
{
	// entity does not have component of type componentType
	if (!HasComponent(entityId, ComponentType::Velocity))
		return false;

	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Velocity)];

	// swap and pop approach to keep vectors tightly packed
	if (index < velocityComponents.size())
	{
		Velocity toRemove = velocityComponents[index];
		Velocity back = velocityComponents.back();

		velocityComponents[velocityComponents.size() - 1] = toRemove;
		velocityComponents[index] = back;

		components[back.entity * componentCount + ComponentIdOffset(ComponentType::Velocity)] = index;
	}

	components[entityId * componentCount + ComponentIdOffset(ComponentType::Velocity)] = -1;
	velocityComponents.pop_back();

	int componentId = static_cast<int>(ComponentType::Velocity);
	entities[entityId].componentMask &= ~componentId;

	return true;
}
/*
=================================================
 Get Components
=================================================
*/

Spatial& Scene::GetSpatialComponent(int entityId)
{
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Spatial)];

	return spatialComponents[index];
}
Sprite& Scene::GetSpriteComponent(int entityId)
{
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Sprite)];

	return spriteComponents[index];
}
Velocity& Scene::GetVelocityComponent(int entityId)
{
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Velocity)];

	return velocityComponents[index];
}
/*
=================================================
 Has Component
=================================================
*/

bool Scene::HasComponent(int entityId, ComponentType componentType)
{
	return (entities[entityId].componentMask & static_cast<int>(componentType)) != 0;
}

/*
===================================================================================================
 Private Functions
===================================================================================================
*/

template<typename T>
bool Scene::AddComponent(int entityId, ComponentType componentType, std::vector<T>& componentList)
{
	// entity already component of type componentType
	if (HasComponent(entityId, componentType))
		return false;

	int componentId = static_cast<int>(componentType);
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);

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
