#pragma once

#include "Scene.h"

class ForceApplierSystem
{
public:
	void Update(Scene& scene, std::vector<Rigidbody>& rigidbodies, float deltaTime);
};