#pragma once

#include "Scene.h"
#include "ForceReceiver.h"

#include <vector>

class ForceApplierSystem
{
public:
	void Update(Scene& scene, std::vector<ForceReceiver>& forceReceivers, float deltaTime);
};