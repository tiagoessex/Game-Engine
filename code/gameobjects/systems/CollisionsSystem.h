

/**

		limited collisions pairs => one system is enough
		handles: 
			- collisions
			- rigidbody
*/


#ifndef __CollisionsSystem_H__
#define __CollisionsSystem_H__


#include "BaseSystem.h"


class btDiscreteDynamicsWorld;

namespace Venator {
	namespace GameObjectComponentSystem	{
		class CollisionsSystem;
	}
}

class Venator::GameObjectComponentSystem::CollisionsSystem : public BaseSystem {

	btDiscreteDynamicsWorld* phyworld;
	public:		
		CollisionsSystem(void);
		~CollisionsSystem(void);

		void update(const std::vector<GameObject*>& gos);
		void enter();
		void exit();

};


#endif