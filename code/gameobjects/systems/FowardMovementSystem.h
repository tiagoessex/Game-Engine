

/**
		move forward - local z axis

		required components:
			- position
			- orientation
			- speed
			- forward
		
*/


#ifndef __FowardMovementSystem_H__
#define __FowardMovementSystem_H__


#include "BaseSystem.h"
//#include "../../Prerequisites.h"

namespace Venator {
	namespace InputEngine {
		class InputManager;
	}
	namespace GameObjectComponentSystem	{
		class FowardMovementSystem;
	}
}


class Venator::GameObjectComponentSystem::FowardMovementSystem : public BaseSystem {
	public:		
		FowardMovementSystem(void);
		~FowardMovementSystem(void);			

		void update(GameObject* c);		// each go - called by _updateSystem
		void enter();					// called by systemsmanager during system init
		void exit();					// called by systemsmanager during system finalizing
			


};		// class FowardMovementSystem


#endif