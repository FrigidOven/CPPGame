#pragma once

#include "Component.h"
#include <raylib.h>

struct CameraManager : Component
{
	static const ComponentID ID = ComponentID::CameraManager;

	Camera2D* camera;

	CameraManager(int entityId, Camera2D* camera)
		: camera(camera)
	{
		entity = entityId;
	}
};