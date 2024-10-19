#pragma once

#include <vector>
#include <unordered_map>

#include "Entity.h"
#include "Components.h"
#include "Systems.h"

/*
* =================================================
* SCENE
* =================================================
*/

class Scene
{
private:

	std::vector<Entity> entities;
	std::vector<int> components; // holds indecies into component lists for each entity

	// key = component id, value = vector<component>
	std::unordered_map<int, void*> componentTable;

	SpriteRendererSystem& spriteRendererSystem;
	VelocitySystem& velocitySystem;
	AccelerationSystem& accelerationSystem;
	ForceSystem& forceSystem;
	SpeedLimiterSystem& speedLimiterSystem;
	InputSystem& inputSystem;
	PlayerActionSystem& playerActionSystem;

public:
	Scene(SpriteRendererSystem& spriteRendererSystem,
		VelocitySystem& velocitySystem,
		AccelerationSystem& accelerationSystem,
		ForceSystem& forceSystem,
		SpeedLimiterSystem& speedLimiterSystem,
		InputSystem& inputSystem,
		PlayerActionSystem& playerActionSystem);

	int CreateEntity();
	void Update();

	template<typename T, typename... Args>
	bool AddComponent(int entityId, Args... args);

	template<typename T>
	bool RemoveComponent(int entityId);

	template<typename T>
	T& GetComponent(int entityId);

	template<typename T>
	bool HasComponent(int entityId);
};

template<typename T, typename... Args>
bool Scene::AddComponent(int entityId, Args... args)
{
	bool successful = !HasComponent<T>(entityId);

	if (successful)
	{
		entities[entityId].componentMask |= 1 << T::ID;
		std::vector<T>* componentList = static_cast<std::vector<T>*>(componentTable[T::ID]);
		componentList->emplace_back(entityId, args...);
		components[entityId * Component::COMPONENT_COUNT + T::ID] = static_cast<int>(componentList->size()) - 1;
	}

	return successful;
}

template<typename T>
bool Scene::RemoveComponent(int entityId)
{
	bool successful = HasComponent<T>(entityId);

	if (successful)
	{
		int index = components[entityId * Component::COMPONENT_COUNT + T::ID];
		std::vector<T>* componentList;
		componentList = static_cast<std::vector<T>*>(componentTable[T::ID]);

		// swap and pop approach to keep vectors tightly packed
		if (index < componentList->size())
		{
			T toRemove = (*componentList)[index];
			T back = componentList->back();

			(*componentList)[componentList->size() - 1] = toRemove;
			(*componentList)[index] = back;

			components[back.entity * Component::COMPONENT_COUNT + T::ID] = index;
		}

		components[entityId * Component::COMPONENT_COUNT + T::ID] = -1;
		componentList->pop_back();

		entities[entityId].componentMask &= ~(1 << T::ID);
	}

	return successful;
}

template<typename T>
T& Scene::GetComponent(int entityId)
{
	int index = components[entityId * Component::COMPONENT_COUNT + T::ID];

	std::vector<T>* componentList;
	componentList = static_cast<std::vector<T>*>(componentTable[T::ID]);

	return (*componentList)[index];
}

template<typename T>
bool Scene::HasComponent(int entityId)
{
	return  (entities[entityId].componentMask & (1 << T::ID)) != 0;
}