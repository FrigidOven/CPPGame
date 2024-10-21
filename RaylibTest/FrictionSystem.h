#pragma once

#include "Friction.h"

#include <vector>

class Scene;

class FrictionSystem
{
public:
	void Update(Scene* scene, std::vector<Friction>& frictions);
};