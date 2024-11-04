#pragma once

#include "Scene.h"

class ImpulseSystem
{
public:
	void Update(Scene& scene, std::vector<Impulse>& impulses, float deltaTime);
};