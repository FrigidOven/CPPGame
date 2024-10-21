#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
Scene::Scene(
	InputSystem& inputSystem,
	ForceBasedMovementControllerSystem& forceBasedMovementControllerSystem,
	VelocityBasedMovementControllerSystem& velocityBasedMovementControllerSystem,
	ForceSystem& forceSystem,
	FrictionSystem& frictionSystem,
	AccelerationSystem& accelerationSystem,
	VelocitySystem& velocitySystem,
	ForceBasedSpeedLimiterSystem& forceBasedSpeedLimiterSystem,
	VelocityBasedSpeedLimiterSystem& velocityBasedSpeedLimiterSystem,
	SpriteRendererSystem& spriteRendererSystem)
	: inputSystem(inputSystem)
	, forceBasedMovementControllerSystem(forceBasedMovementControllerSystem)
	, velocityBasedMovementControllerSystem(velocityBasedMovementControllerSystem)
	, forceSystem(forceSystem)
	, frictionSystem(frictionSystem)
	, accelerationSystem(accelerationSystem)
	, velocitySystem(velocitySystem)
	, forceBasedSpeedLimiterSystem(forceBasedSpeedLimiterSystem)
	, velocityBasedSpeedLimiterSystem(velocityBasedSpeedLimiterSystem)
	, spriteRendererSystem(spriteRendererSystem)
{
		componentTable[Spatial::ID] = static_cast<void*>(new std::vector<Spatial>);
		componentTable[BackgroundSprite::ID] = static_cast<void*>(new std::vector<BackgroundSprite>);
		componentTable[MiddlegroundSprite::ID] = static_cast<void*>(new std::vector<MiddlegroundSprite>);
		componentTable[ForegroundSprite::ID] = static_cast<void*>(new std::vector<ForegroundSprite>);
		componentTable[Velocity::ID] = static_cast<void*>(new std::vector<Velocity>);
		componentTable[Acceleration::ID] = static_cast<void*>(new std::vector<Acceleration>);
		componentTable[Mass::ID] = static_cast<void*>(new std::vector<Mass>);
		componentTable[Force::ID] = static_cast<void*>(new std::vector<Force>);
		componentTable[Friction::ID] = static_cast<void*>(new std::vector<Friction>);
		componentTable[ForceBasedSpeedLimiter::ID] = static_cast<void*>(new std::vector<ForceBasedSpeedLimiter>);
		componentTable[VelocityBasedSpeedLimiter::ID] = static_cast<void*>(new std::vector<VelocityBasedSpeedLimiter>);
		componentTable[ForceBasedMovement::ID] = static_cast<void*>(new std::vector<ForceBasedMovement>);
		componentTable[VelocityBasedMovement::ID] = static_cast<void*>(new std::vector<VelocityBasedMovement>);
		componentTable[ForceBasedMovementController::ID] = static_cast<void*>(new std::vector<ForceBasedMovementController>);
		componentTable[VelocityBasedMovementController::ID] = static_cast<void*>(new std::vector<VelocityBasedMovementController>);
}
Scene::~Scene()
{
	delete(static_cast<std::vector<Spatial>*>(componentTable[Spatial::ID]));
	delete(static_cast<std::vector<BackgroundSprite>*>(componentTable[BackgroundSprite::ID]));
	delete(static_cast<std::vector<MiddlegroundSprite>*>(componentTable[MiddlegroundSprite::ID]));
	delete(static_cast<std::vector<ForegroundSprite>*>(componentTable[ForegroundSprite::ID]));
	delete(static_cast<std::vector<Velocity>*>(componentTable[Velocity::ID]));
	delete(static_cast<std::vector<Acceleration>*>(componentTable[Acceleration::ID]));
	delete(static_cast<std::vector<Mass>*>(componentTable[Mass::ID]));
	delete(static_cast<std::vector<Force>*>(componentTable[Force::ID]));
	delete(static_cast<std::vector<Friction>*>(componentTable[Friction::ID]));
	delete(static_cast<std::vector<ForceBasedSpeedLimiter>*>(componentTable[ForceBasedSpeedLimiter::ID]));
	delete(static_cast<std::vector<VelocityBasedSpeedLimiter>*>(componentTable[VelocityBasedSpeedLimiter::ID]));
	delete(static_cast<std::vector<ForceBasedMovement>*>(componentTable[ForceBasedMovement::ID]));
	delete(static_cast<std::vector<VelocityBasedMovement>*>(componentTable[VelocityBasedMovement::ID]));
	delete(static_cast<std::vector<ForceBasedMovementController>*>(componentTable[ForceBasedMovementController::ID]));
	delete(static_cast<std::vector<VelocityBasedMovementController>*>(componentTable[VelocityBasedMovementController::ID]));
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
	// RELEVANT COMPONENT LISTS:
	// sprite component lists
	auto& backgroundSprites = *(static_cast<std::vector<BackgroundSprite>*>(componentTable[BackgroundSprite::ID]));
	auto& middlegroundSprites = *(static_cast<std::vector<MiddlegroundSprite>*>(componentTable[MiddlegroundSprite::ID]));
	auto& foregroundSprites = *(static_cast<std::vector<ForegroundSprite>*>(componentTable[ForegroundSprite::ID]));
	// physics related component lists
	auto& velocities = *(static_cast<std::vector<Velocity>*>(componentTable[Velocity::ID]));
	auto& accelerations = *(static_cast<std::vector<Acceleration>*>(componentTable[Acceleration::ID]));
	auto& frictions = *(static_cast<std::vector<Friction>*>(componentTable[Friction::ID]));
	auto& forces = *(static_cast<std::vector<Force>*>(componentTable[Force::ID]));
	// speed limiter component lists
	auto& forceBasedSpeedLimiters = *(static_cast<std::vector<ForceBasedSpeedLimiter>*>(componentTable[Force::ID]));
	auto& velocityBasedSpeedLimiters = *(static_cast<std::vector<VelocityBasedSpeedLimiter>*>(componentTable[Friction::ID]));
	// movement component lists
	auto& forceBasedMovements = *(static_cast<std::vector<ForceBasedMovement>*>(componentTable[Force::ID]));
	auto& velocityBasedMovements = *(static_cast<std::vector<VelocityBasedMovement>*>(componentTable[Friction::ID]));
	// movement controller component lists
	auto& forceBasedMovementControllers = *(static_cast<std::vector<ForceBasedMovementController>*>(componentTable[Force::ID]));
	auto& velocityBasedMovementControllers = *(static_cast<std::vector<VelocityBasedMovementController>*>(componentTable[Friction::ID]));
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Input Routine:
	inputSystem.Update(this, forceBasedMovementControllers, velocityBasedMovementControllers);
	forceBasedMovementControllerSystem.Update(this, forceBasedMovementControllers);
	velocityBasedMovementControllerSystem.Update(this, velocityBasedMovementControllers);

	// Physics Routine:
	frictionSystem.Update(this, frictions);
	forceSystem.Update(this, forces);
	accelerationSystem.Update(this, accelerations);
	forceBasedSpeedLimiterSystem.Update(this, forceBasedSpeedLimiters);
	velocityBasedSpeedLimiterSystem.Update(this, velocityBasedSpeedLimiters);
	velocitySystem.Update(this, velocities);

	// Rendering Routine:
	spriteRendererSystem.Update(this, backgroundSprites, middlegroundSprites, foregroundSprites);
}
