#include <vector>
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void InputSystem::Update(Scene* scene, std::vector<PlayerInputListener> playerInputListenerComponents)
{
	switch (inputMode)
	{
	case Default:
		UpdatePlayerInputListeners(scene, playerInputListenerComponents);
		break;
	}
}
/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void InputSystem::UpdatePlayerInputListeners(Scene* scene, std::vector<PlayerInputListener> playerInputListenerComponents)
{

}