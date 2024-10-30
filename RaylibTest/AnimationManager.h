#pragma once

#include "AnimationData.h"
#include <raylib.h>

class AnimationManager
{
private:


public:
	AnimationManager();

	const Texture2D& GetBackgroundTexture();
	const Texture2D& GetPlayerTexture();
};