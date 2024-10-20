#pragma once

#include "raylib.h"

class Scene;

struct Command
{
	virtual void Execute(Scene* scene, int entityId) = 0;
};

struct MovementCommand : Command
{
	Vector2 force;

	void Execute(Scene* scene, int entityId) override;

	MovementCommand(Vector2 force)
		: force(force)
	{
	}
};