#pragma once

#include "Component.h"
#include <raylib.h>

struct CameraManager : Component
{
	static const int ID = 15;

	Camera2D* camera;

	CameraManager(int entityId, Camera2D* camera)
		: camera(camera)
	{
		entity = entityId;
	}
};