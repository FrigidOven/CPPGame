#pragma once

#include "Scene.h"
#include "Impulse.h"

#include <vector>

class ImpulseSystem
{
public:
	void Update(Scene& scene, std::vector<Impulse>& impulses, float deltaTime);
};