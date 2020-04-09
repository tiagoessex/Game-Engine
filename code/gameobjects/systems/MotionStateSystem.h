

/**

*/


#ifndef __MotionStateSystem_H__
#define __MotionStateSystem_H__


#include "BaseSystem.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class MotionStateSystem;
	}
}

class Venator::GameObjectComponentSystem::MotionStateSystem : public BaseSystem {
	public:		
		MotionStateSystem(void);
		~MotionStateSystem(void);

		void update(GameObject* go);
		void enter();
		void exit();

};


#endif