#pragma once

#include "Component.h"
#include "Tags.h"

struct Tag : Component
{
	static const ComponentID ID = ComponentID::Tag;

	EntityGroup entityGroup;
	EntityType entityType;
	Direction direction;
	State state;

	Tag(int entityId)
		: entityGroup(EntityGroup::None)
		, entityType(EntityType::None)
		, direction(Direction::None)
		, state(State::Idle)
	{
		entity = entityId;
	}
};