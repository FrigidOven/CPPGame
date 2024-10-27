#pragma once

#include "Scene.h"
#include "Friction.h"

#include <vector>

class FrictionSystem
{
public:
	void Update(Scene& scene, std::vector<Friction>& frictions);
};