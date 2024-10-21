#pragma once

#include "Component.h"
#include "Input.h"
#include <raylib.h>

struct ForceBasedMovementController : Component
{
	static const int ID = 13;

	float force;

	Input up;
	Input left;
	Input down;
	Input right;

	InputListener inputListener;

	ForceBasedMovementController(int entityId, float force, Input up, Input left, Input down, Input right)
		: force(force)
		, up(up)
		, left(left)
		, down(down)
		, right(right)
	{
		entity = entityId;

		inputListener.ListenForInput(up);
		inputListener.ListenForInput(left);
		inputListener.ListenForInput(down);
		inputListener.ListenForInput(right);
	}
};