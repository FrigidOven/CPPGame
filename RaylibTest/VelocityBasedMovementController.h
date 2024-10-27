#pragma once

#include "Component.h"
#include "Input.h"
#include <raylib.h>

struct VelocityBasedMovementController : Component
{
	static const int ID = 12;

	float speed;

	Input up;
	Input left;
	Input down;
	Input right;

	InputListener inputListener;

	VelocityBasedMovementController(int entityId, float speed, Input up, Input left, Input down, Input right)
		: speed(speed)
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