#pragma once

#include "Scene.h"
#include "FollowCamera.h"

#include <vector>

class FollowCameraSystem
{
public:
	void Update(Scene& scene, std::vector<FollowCamera>& followCameras);
};