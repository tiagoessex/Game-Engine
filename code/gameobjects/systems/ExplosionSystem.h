

/**

*/


#ifndef __ExplosionSystem_H__
#define __ExplosionSystem_H__


#include "BaseSystem.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class ExplosionSystem;
	}
}

class Venator::GameObjectComponentSystem::ExplosionSystem : public BaseSystem {
	public:		
		ExplosionSystem(void);
		~ExplosionSystem(void);			

		void update(Component* go);
		void enter();				
		void exit();				
						
};


#endif