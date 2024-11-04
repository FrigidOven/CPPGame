#pragma once

#include "Component.h"
#include <raylib.h>

struct FollowCamera : Component
{
	static const ComponentID ID = ComponentID::FollowCamera;

	int targetEntity;
	Vector2 offset;

	FollowCamera(int entityId, int targetEntityId, Vector2 offset)
		: targetEntity(targetEntityId)
		, offset(offset)
	{
		entity = entityId;
	}
};