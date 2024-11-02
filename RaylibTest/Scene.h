#pragma once

#include <array>

#include "Entity.h"
#include "Components.h"

enum class SpecialEntities
{
	Camera = 0
};

class Scene
{
private:

	// all entities in the scene
	std::vector<Entity> entities;
	// indecies into component lists for each entity
	std::vector<int> components;

	// all component lists
	std::vector<Tag> tags;
	std::vector<Spatial> spatials;
	std::vector<Sprite> sprites;
	std::vector<Controller> controllers;
	// for rendering sprites are also sorted by y-value and layer
	std::vector<int> sortedSpriteIndices;
	std::vector<Velocity> velocities;
	std::vector<Acceleration> accelerations;
	std::vector<Mass> masses;
	std::vector<Force> forces;
	std::vector<Friction> frictions;
	std::vector<StoppingForce> stoppingForces;
	std::vector<MovementController> movementControllers;
	std::vector<Movement> movements;
	std::vector<SpeedLimiter> speedLimiters;
	std::vector<SpriteManager> spriteManagers;
	std::vector<CameraManager> cameraManagers;
	std::vector<FollowCamera> followCameras;

	// TODO: Consider layers for physics too, for dynamically switching which hitboxes should be checked.

	// table of components for generalized access
	void* componentLists[16]
	{
		&tags,
		&spatials,
		&sprites,
		&controllers,
		&velocities,
		&accelerations,
		&masses,
		&forces,
		&frictions,
		&stoppingForces,
		&movementControllers,
		&movements,
		&speedLimiters,
		&spriteManagers,
		&cameraManagers,
		&followCameras
	};

public:
	Scene(Camera2D* camera);

	int CreateEntity();

	template< typename T, typename... Args >
	bool AddComponent(int entityId, Args... args);

	template<typename T>
	bool RemoveComponent(int entityId);

	template<typename T>
	T& GetComponent(int entityId);

	std::vector<int>& GetSortedSpriteIndices();

	template<typename T>
	std::vector<T>& GetComponents();

	template<typename T>
	bool HasComponent(int entityId);

	int GetComponentMask(int entityId);
};

template<typename T, typename... Args>
bool Scene::AddComponent(int entityId, Args... args)
{
	bool successful = !HasComponent<T>(entityId);

	if (successful)
	{
		entities[entityId].componentMask |= 1 << T::ID;
		std::vector<T>* componentList = static_cast<std::vector<T>*>(componentLists[T::ID]);
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
		std::vector<T>* componentList = static_cast<std::vector<T>*>(componentLists[T::ID]);

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
	return (*static_cast<std::vector<T>*>(componentLists[T::ID]))[index];
}

template<typename T>
std::vector<T>&  Scene::GetComponents()
{
	return *(static_cast<std::vector<T>*>(componentLists[T::ID]));
}

template<typename T>
bool Scene::HasComponent(int entityId)
{
	return  (entities[entityId].componentMask & (1 << T::ID)) != 0;
}