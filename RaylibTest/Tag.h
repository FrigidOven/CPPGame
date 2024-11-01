#pragma once

#include "Component.h"
#include "Tags.h"

struct Tag : Component
{
	static const int ID = 17;

	EntityGroup entityGroup;
	EntityType entityType;
	Direction direction;
	State state;

	Tag(int entityId)
	{
		entity = entityId;
	}
	Tag(int entityId, EntityGroup entityGroup, EntityType entityType, Direction direction, State state)
		: entityGroup(entityGroup)
		, entityType(entityType)
		, direction(direction)
		, state(state)
	{
		entity = entityId;
	}
};