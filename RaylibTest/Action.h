#pragma once

#include "raylib.h"

class Scene;

struct Action
{
	virtual void Execute(Scene* scene, int entityId) = 0;
};

struct MovementAction : Action
{
	Vector2 force;

	MovementAction(Vector2 force)
		: force(force)
	{
	}
	void Execute(Scene* scene, int entityId) override;
};