#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
Scene::Scene(SpriteRendererSystem& spriteRendererSystem,
	VelocitySystem& velocitySystem,
	AccelerationSystem& accelerationSystem,
	ForceSystem& forceSystem,
	SpeedLimiterSystem& speedLimiterSystem,
	InputSystem& inputSystem,
	PlayerActionSystem& playerActionSystem,
	ActionSystem& actionSystem)
	: spriteRendererSystem(spriteRendererSystem)
	, velocitySystem(velocitySystem)
	, accelerationSystem(accelerationSystem)
	, forceSystem(forceSystem)
	, speedLimiterSystem(speedLimiterSystem)
	, inputSystem(inputSystem)
	, playerActionSystem(playerActionSystem)
	, actionSystem(actionSystem)
{
		componentTable[Spatial::ID] = static_cast<void*>(new std::vector<Spatial>);
		componentTable[Sprite::ID] = static_cast<void*>(new std::vector<Sprite>);
		componentTable[RigidBody::ID] = static_cast<void*>(new std::vector<RigidBody>);
		componentTable[Force::ID] = static_cast<void*>(new std::vector<Force>);
		componentTable[SpeedLimiter::ID] = static_cast<void*>(new std::vector<SpeedLimiter>);
		componentTable[PlayerInputListener::ID] = static_cast<void*>(new std::vector<PlayerInputListener>);
		componentTable[Action::ID] = static_cast<void*>(new std::vector<Action>);
}
Scene::~Scene()
{
	delete(static_cast<std::vector<Spatial>*>(componentTable[Spatial::ID]));
	delete(static_cast<std::vector<Sprite>*>(componentTable[Sprite::ID]));
	delete(static_cast<std::vector<RigidBody>*>(componentTable[RigidBody::ID]));
	delete(static_cast<std::vector<Force>*>(componentTable[Force::ID]));
	delete(static_cast<std::vector<SpeedLimiter>*>(componentTable[SpeedLimiter::ID]));
	delete(static_cast<std::vector<PlayerInputListener>*>(componentTable[PlayerInputListener::ID]));
	delete(static_cast<std::vector<Action>*>(componentTable[Action::ID]));
}

int Scene::CreateEntity()
{
	entities.emplace_back
	(
		static_cast<int>(entities.size()),	// id
		0															// component mask
	);

	// reserve space for all components even if the entity wont use them all
	int componentCount = static_cast<int>(Component::COMPONENT_COUNT);
	components.resize(components.size() + componentCount, -1);

	return static_cast<int>(entities.size()) - 1;
}
void Scene::Update()
{
	// Relevant Component Lists
	auto& spriteComponents = *(static_cast<std::vector<Sprite>*>(componentTable[Sprite::ID]));
	auto& rigidBodyComponents = *(static_cast<std::vector<RigidBody>*>(componentTable[RigidBody::ID]));
	auto& forceComponents = *(static_cast<std::vector<Force>*>(componentTable[Force::ID]));
	auto& speedLimiterComponents = *(static_cast<std::vector<SpeedLimiter>*>(componentTable[SpeedLimiter::ID]));
	auto& playerInputListenterComponents = *(static_cast<std::vector<PlayerInputListener>*>(componentTable[PlayerInputListener::ID]));
	auto& actionComponents = *(static_cast<std::vector<Action>*>(componentTable[Action::ID]));
	
	// Input Routine:
	// Update order: Input -> PlayerAction -> Action
	inputSystem.Update(this, playerInputListenterComponents);
	playerActionSystem.Update(this, playerInputListenterComponents);
	actionSystem.Update(this, actionComponents);


	// Physics Routine:
	// Update order : Forces -> Acceleration -> SpeedLimiter -> Velocity
	forceSystem.Update(this, forceComponents);
	accelerationSystem.Update(this, rigidBodyComponents);
	speedLimiterSystem.Update(this, speedLimiterComponents);
	velocitySystem.Update(this, rigidBodyComponents);

	// Rendering Routine:
	// Update order: Sprite
	spriteRendererSystem.Draw(this, spriteComponents);
}
