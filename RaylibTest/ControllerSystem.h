#pragma once

#include "Scene.h"

class ControllerSystem
{
private:
	bool CheckDown(int playerNumber, Input& input);
	bool CheckPressed(int playerNumber, Input& input);

public:
	void Update(Scene& scene, std::vector<Controller>& controllers);
};