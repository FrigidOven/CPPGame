#pragma once

#include "GameConstants.h"

#include "Entity.h"

// components
#include "Tag.h"
#include "Spatial.h"
#include "Sprite.h"
#include "Controller.h"
#include "Velocity.h"
#include "Acceleration.h"
#include "Rigidbody.h"
#include "Friction.h"
#include "Impulse.h"
#include "MovementController.h"
#include "Movement.h"
#include "SpriteManager.h"
#include "CameraManager.h"
#include "FollowCamera.h"

#include <array>

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
	std::vector<Rigidbody> rigidbodies;
	std::vector<Friction> frictions;
	std::vector<Impulse> impulses;
	std::vector<MovementController> movementControllers;
	std::vector<Movement> movements;
	std::vector<SpriteManager> spriteManagers;
	std::vector<CameraManager> cameraManagers;
	std::vector<FollowCamera> followCameras;

	// TODO: Consider layers for physics too, for dynamically switching which hitboxes should be checked.

	// table of components for generalized access
	void* componentLists[static_cast<int>(ComponentID::COMPONENT_COUNT)];

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
		entities[entityId].componentMask |= 1 << static_cast<int>(T::ID);
		std::vector<T>* componentList = static_cast<std::vector<T>*>(componentLists[static_cast<int>(T::ID)]);
		componentList->emplace_back(entityId, args...);
		components[entityId * static_cast<int>(ComponentID::COMPONENT_COUNT) + static_cast<int>(T::ID)] = static_cast<int>(componentList->size()) - 1;
	}

	return successful;
}

template<typename T>
bool Scene::RemoveComponent(int entityId)
{
	bool successful = HasComponent<T>(entityId);

	if (successful)
	{
		int index = components[entityId * static_cast<int>(ComponentID::COMPONENT_COUNT) + static_cast<int>(T::ID)];
		std::vector<T>* componentList = static_cast<std::vector<T>*>(componentLists[static_cast<int>(T::ID)]);

		// swap and pop approach to keep vectors tightly packed
		if (index < componentList->size())
		{
			T toRemove = (*componentList)[index];
			T back = componentList->back();

			(*componentList)[componentList->size() - 1] = toRemove;
			(*componentList)[index] = back;

			components[back.entity * static_cast<int>(ComponentID::COMPONENT_COUNT) + static_cast<int>(T::ID)] = index;
		}

		components[entityId * static_cast<int>(ComponentID::COMPONENT_COUNT) + static_cast<int>(T::ID)] = -1;
		componentList->pop_back();

		entities[entityId].componentMask &= ~(1 << static_cast<int>(T::ID));
	}

	return successful;
}

template<typename T>
T& Scene::GetComponent(int entityId)
{
	int index = components[entityId * static_cast<int>(ComponentID::COMPONENT_COUNT) + static_cast<int>(T::ID)];
	return (*static_cast<std::vector<T>*>(componentLists[static_cast<int>(T::ID)]))[index];
}

template<typename T>
std::vector<T>&  Scene::GetComponents()
{
	return *(static_cast<std::vector<T>*>(componentLists[static_cast<int>(T::ID)]));
}

template<typename T>
bool Scene::HasComponent(int entityId)
{
	return  (entities[entityId].componentMask & (1 << static_cast<int>(T::ID))) != 0;
}