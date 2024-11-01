#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/

Scene::Scene(Camera2D* camera)
{
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
	int componentCount = static_cast<int>(Component::COMPONENT_COUNT);
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
