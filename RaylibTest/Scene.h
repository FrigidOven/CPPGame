#pragma once

#include <array>

#include "Entity.h"
#include "Components.h"

class Scene
{
private:

	// all entities in the scene
	std::vector<Entity> entities;
	// indecies into component lists for each entity
	std::vector<int> components;

	// all component lists

	std::vector<Spatial> spatials;
	// sprites are organized into layers
	std::array<std::vector<Sprite>, 16> sprites
	{ {
		{ },	// layer-zero sprites
		{ },	// layer-one sprites
		{ },	// ...
		{ },
		{ },
		{ },
		{ },
		{ },
		{ },
		{ },
		{ },
		{ },
		{ },
		{ },
		{ },
		{ }   // layer-sixteen sprites
	} };
	std::vector<Velocity> velocities;
	std::vector<Acceleration> accelerations;
	std::vector<Mass> masses;
	std::vector<Force> forces;
	std::vector<Friction> frictions;
	std::vector<ForceBasedSpeedLimiter> forceBasedSpeedLimiters;
	std::vector<VelocityBasedSpeedLimiter> velocityBasedSpeedLimiters;
	std::vector<ForceBasedMovement> forceBasedMovements;
	std::vector<VelocityBasedMovement> velocityBasedMovements;
	std::vector<ForceBasedMovementController> forceBasedMovementControllers;
	std::vector<VelocityBasedMovementController> velocityBasedMovementControllers;
	std::vector<SpriteManager> spriteManagers;
	std::vector<StoppingForce> stoppingForces;

	// TODO: Consider layers for physics too, for dynamically switching which hitboxes should be checked.

	// table of components for generalized access
	void* componentLists[17]
	{
		&spatials,
		nullptr,				// sprites aren't held here
		&velocities,
		&accelerations,
		&masses,
		&forces,
		&frictions,
		&forceBasedSpeedLimiters,
		&velocityBasedSpeedLimiters,
		&forceBasedMovements,
		&velocityBasedMovements,
		&forceBasedMovementControllers,
		&velocityBasedMovementControllers,
		&spriteManagers,
		&stoppingForces
	};

public:
	int CreateEntity(EntityTag tag);

	template< typename T, typename... Args >
	typename std::enable_if<!std::is_same<T, Sprite>::value, bool>::type
	AddComponent(int entityId, Args... args);

	template<typename T>
	typename std::enable_if<!std::is_same<T, Sprite>::value, bool>::type
	RemoveComponent(int entityId);

	template<typename T>
	typename std::enable_if<!std::is_same<T, Sprite>::value, T&>::type
	GetComponent(int entityId);

	template<typename T>
	typename std::enable_if<!std::is_same<T, Sprite>::value, std::vector<T>&>::type
	GetComponents();

	// sprites are handled differently so they are excluded by
	// the template and handled here instead
	bool AddSpriteComponent(int entityId, int layer, Texture2D* source, Rectangle sourceRect, float destWidth, float destHeight, int frameCount, int currentFrame, float fps);
	bool RemoveSpriteComponent(int entityId);
	Sprite& GetSpriteComponent(int entityId);
	std::array<std::vector<Sprite>, 16>& GetSpriteComponents();

	template<typename T>
	bool HasComponent(int entityId);

	int GetComponentMask(int entityId);

	EntityTag GetTag(int entityId);
};

template<typename T, typename... Args>
typename std::enable_if<!std::is_same<T, Sprite>::value, bool>::type
Scene::AddComponent(int entityId, Args... args)
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
typename std::enable_if<!std::is_same<T, Sprite>::value, bool>::type
Scene::RemoveComponent(int entityId)
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
typename std::enable_if<!std::is_same<T, Sprite>::value, T&>::type
Scene::GetComponent(int entityId)
{
	int index = components[entityId * Component::COMPONENT_COUNT + T::ID];
	return (*static_cast<std::vector<T>*>(componentLists[T::ID]))[index];
}

template<typename T>
typename std::enable_if<!std::is_same<T, Sprite>::value, std::vector<T>&>::type
Scene::GetComponents()
{
	return *(static_cast<std::vector<T>*>(componentLists[T::ID]));
}

template<typename T>
bool Scene::HasComponent(int entityId)
{
	return  (entities[entityId].componentMask & (1 << T::ID)) != 0;
}