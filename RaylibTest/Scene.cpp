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
	, rigidBodySystem(new RigidBodySystem(*this, rigidBodyComponents))
	, forceSystem(new ForceSystem(*this, forceComponents))
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
	rigidBodySystem->Update();
	forceSystem->Update();
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
bool Scene::AddRigidBodyComponent(int entityId, float mass, Vector2 velocity, float angularVelocity, Vector2 acceleration, float angularAcceleration)
{
	bool successful = AddComponent<RigidBody>(entityId, ComponentType::RigidBody, rigidBodyComponents);

	if (!successful)
		return successful;

	rigidBodyComponents.emplace_back
	(
		entityId,
		mass,
		velocity,
		angularVelocity,
		acceleration,
		angularAcceleration
	);

	return successful;
}
bool Scene::AddForceComponent(int entityId, Vector2 force, float angularForce)
{
	bool successful = AddComponent<Force>(entityId, ComponentType::Force, forceComponents);

	if (!successful)
		return successful;

	forceComponents.emplace_back
	(
		entityId,
		force,
		angularForce
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
bool Scene::RemoveRigidBodyComponent(int entityId)
{
	// entity does not have component of type componentType
	if (!HasComponent(entityId, ComponentType::RigidBody))
		return false;

	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::RigidBody)];

	// swap and pop approach to keep vectors tightly packed
	if (index < rigidBodyComponents.size())
	{
		RigidBody toRemove = rigidBodyComponents[index];
		RigidBody back = rigidBodyComponents.back();

		rigidBodyComponents[rigidBodyComponents.size() - 1] = toRemove;
		rigidBodyComponents[index] = back;

		components[back.entity * componentCount + ComponentIdOffset(ComponentType::RigidBody)] = index;
	}

	components[entityId * componentCount + ComponentIdOffset(ComponentType::RigidBody)] = -1;
	rigidBodyComponents.pop_back();

	int componentId = static_cast<int>(ComponentType::RigidBody);
	entities[entityId].componentMask &= ~componentId;

	return true;
}
bool Scene::RemoveForceComponent(int entityId)
{
	// entity does not have component of type componentType
	if (!HasComponent(entityId, ComponentType::Force))
		return false;

	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Force)];

	// swap and pop approach to keep vectors tightly packed
	if (index < forceComponents.size())
	{
		Force toRemove = forceComponents[index];
		Force back = forceComponents.back();

		forceComponents[forceComponents.size() - 1] = toRemove;
		forceComponents[index] = back;

		components[back.entity * componentCount + ComponentIdOffset(ComponentType::Force)] = index;
	}

	components[entityId * componentCount + ComponentIdOffset(ComponentType::Force)] = -1;
	forceComponents.pop_back();

	int componentId = static_cast<int>(ComponentType::Force);
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
RigidBody& Scene::GetRigidBodyComponent(int entityId)
{
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::RigidBody)];

	return rigidBodyComponents[index];
}
Force& Scene::GetForceComponent(int entityId)
{
	int componentCount = static_cast<int>(ComponentType::NUMBER_OF_COMPONENTS);
	int index = components[entityId * componentCount + ComponentIdOffset(ComponentType::Force)];

	return forceComponents[index];
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
