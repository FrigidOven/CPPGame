#include "FollowCameraSystem.h"
#include "Scene.h"
#include "GameConstants.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void FollowCameraSystem::Update(Scene& scene, std::vector<FollowCamera>& followCameras)
{
	int requiredComponentsMask = (1 << CameraManager::ID);

	for (auto& followCamera : followCameras)
	{
		if ((scene.GetComponentMask(followCamera.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		CameraManager& cameraManager = scene.GetComponent<CameraManager>(followCamera.entity);

		Camera2D* camera = scene.GetComponent<CameraManager>(followCamera.entity).camera;

		Vector2 targetPosition = Vector2Zero();
		if (scene.HasComponent<Spatial>(followCamera.entity))
			camera->target = scene.GetComponent<Spatial>(followCamera.targetEntity).position;

		camera->offset = Vector2Add(followCamera.offset, Vector2((float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f));
	}
}