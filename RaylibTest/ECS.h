#pragma once

#include "Scene.h"


/*
*							ECS
*							   |
*						  SCENE ----> UNORDERED_MAP
*						/			 \
*			  ENTITY	         SYSTEMS ----> VECTOR
*									/			   \
*							 INPUT			  COMPONENTS
*												/						\
*										RAYLIB				RAYMATH
*/