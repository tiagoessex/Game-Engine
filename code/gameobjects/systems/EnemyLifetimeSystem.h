

/**
		handles: 
			- enemylifetime
			- position


*/


#ifndef __EnemyLifetimeSystem_H__
#define __EnemyLifetimeSystem_H__


#include "BaseSystem.h"
//#include "../../Prerequisites.h"

namespace Venator {
	namespace GameObjectComponentSystem	{
		class EnemyLifetimeSystem;
	}
}

class Venator::GameObjectComponentSystem::EnemyLifetimeSystem : public BaseSystem {
	public:		
		EnemyLifetimeSystem(void);
		~EnemyLifetimeSystem(void);			

		void update(GameObject* c);	
		void enter();				
		void exit();				
};	


#endif