#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/

Scene::Scene(Camera2D* camera)
{
	// initialize component lists
	componentLists[static_cast<int>(ComponentID::Tag)] = &tags;
	componentLists[static_cast<int>(ComponentID::Spatial)] = &spatials;
	componentLists[static_cast<int>(ComponentID::Sprite)] = &sprites;
	componentLists[static_cast<int>(ComponentID::Controller)] = &controllers;
	componentLists[static_cast<int>(ComponentID::Velocity)] = &velocities;
	componentLists[static_cast<int>(ComponentID::Acceleration)] = &accelerations;
	componentLists[static_cast<int>(ComponentID::Rigidbody)] = &rigidbodies;
	componentLists[static_cast<int>(ComponentID::Friction)] = &frictions;
	componentLists[static_cast<int>(ComponentID::Impulse)] = &impulses;
	componentLists[static_cast<int>(ComponentID::MovementController)] = &movementControllers;
	componentLists[static_cast<int>(ComponentID::Movement)] = &movements;
	componentLists[static_cast<int>(ComponentID::SpeedLimiter)] = &speedLimiters;
	componentLists[static_cast<int>(ComponentID::SpriteManager)] = &spriteManagers;
	componentLists[static_cast<int>(ComponentID::CameraManager)] = &cameraManagers;
	componentLists[static_cast<int>(ComponentID::FollowCamera)] = &followCameras;

	// initialize camera
	int cameraEntity = CreateEntity();
	AddComponent<CameraManager>(cameraEntity, camera);
	AddComponent<Spatial>(cameraEntity, Vector2Zero(), 0.0f);
	Tag& tag = GetComponent<Tag>(cameraEntity);
	tag.entityGroup = EntityGroup::Engine;
	tag.entityType = EntityType::Camera;
}

int Scene::CreateEntity()
{
	int id = static_cast<int>(entities.size());
	int componentMask = 0;

	entities.emplace_back
	(
		id,	
		componentMask
	);

	// reserve space for all components even if the entity wont use them all
	int componentCount = static_cast<int>(ComponentID::COMPONENT_COUNT);
	components.resize(components.size() + componentCount, -1);

	// each entity MUST have a tag component
	AddComponent<Tag>(id);

	return id;
}

std::vector<int>& Scene::GetSortedSpriteIndices()
{
	return sortedSpriteIndices;
}

int Scene::GetComponentMask(int entityId)
{
	return entities[entityId].componentMask;
}
