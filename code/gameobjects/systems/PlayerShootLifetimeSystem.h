

/**
		handles: 
			- playershootlifetime
			- position


*/


#ifndef __PlayerShootLifetimeSystem_H__
#define __PlayerShootLifetimeSystem_H__


#include "BaseSystem.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class PlayerShootLifetimeSystem;
	}
}

class Venator::GameObjectComponentSystem::PlayerShootLifetimeSystem : public BaseSystem {
	public:		
		PlayerShootLifetimeSystem(void);
		~PlayerShootLifetimeSystem(void);			

		void update(GameObject* c);	
		void enter();				
		void exit();				
};	


#endif