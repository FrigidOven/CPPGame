#pragma once

#include "Scene.h"

class FrictionSystem
{
public:
	void Update(Scene& scene, std::vector<Friction>& frictions);
};