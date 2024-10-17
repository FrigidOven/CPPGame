#include <vector>
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
Scene::Scene(SpriteRendererSystem& spriteRendererSystem,
	RigidBodySystem& rigidBodySystem,
	ForceSystem& forceSystem,
	SpeedLimiterSystem& speedLimiterSystem,
	InputSystem& inputSystem,
	PlayerActionSystem& playerActionSystem)
	: spriteRendererSystem(spriteRendererSystem)
	, rigidBodySystem(rigidBodySystem)
	, forceSystem(forceSystem)
	, speedLimiterSystem(speedLimiterSystem)
	, inputSystem(inputSystem)
	, playerActionSystem(playerActionSystem)
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
	int componentCount = static_cast<int>(Component::COMPONENT_COUNT);
	components.resize(components.size() + componentCount, -1);

	return static_cast<int>(entities.size()) - 1;
}
void Scene::Update()
{
	if (componentTable.find(PlayerInputListener::ID) != componentTable.end())
	{
		auto& playerInputListenterComponents = *(static_cast<std::vector<PlayerInputListener>*>(componentTable[PlayerInputListener::ID]));
		inputSystem.Update(this, playerInputListenterComponents);
		playerActionSystem.Update(this, playerInputListenterComponents);
	}
	if (componentTable.find(Sprite::ID) != componentTable.end())
	{
		auto& spriteComponents = *(static_cast<std::vector<Sprite>*>(componentTable[Sprite::ID]));
		spriteRendererSystem.Draw(this, spriteComponents);
	}
	if (componentTable.find(SpeedLimiter::ID) != componentTable.end())
	{
		auto& speedLimiterComponents = *(static_cast<std::vector<SpeedLimiter>*>(componentTable[SpeedLimiter::ID]));
		speedLimiterSystem.Update(this, speedLimiterComponents);
	}
	if (componentTable.find(RigidBody::ID) != componentTable.end())
	{
		auto& rigidBodyComponents = *(static_cast<std::vector<RigidBody>*>(componentTable[RigidBody::ID]));
		rigidBodySystem.Update(this, rigidBodyComponents);
	}
	if (componentTable.find(Force::ID) != componentTable.end())
	{
		auto& forceComponents = *(static_cast<std::vector<Force>*>(componentTable[Force::ID]));
		forceSystem.Update(this, forceComponents);
	}

}
/*
===================================================================================================
 Private Functions
===================================================================================================
*/
int Scene::ComponentIdOffset(int componentId)
{
	int componentIdOffset = 0;
	for (componentIdOffset = 0; (componentId & 1) == 0; componentIdOffset++)
	{
		componentId >>= 1;
	}
	return componentIdOffset;
}
