#pragma once

#include "Scene.h"

class FollowCameraSystem
{
public:
	void Update(Scene& scene, std::vector<FollowCamera>& followCameras);
};