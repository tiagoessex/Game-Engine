

/**
	ATT:
		- all position/scale/orientations changes should be done by the SceneNodeAnimationsSystem
			=> can not be handle by renderXXXXsystem / FowardMovementSystem / ...
*/


#ifndef __SceneNodeAnimationsSystem_H__
#define __SceneNodeAnimationsSystem_H__


#include "BaseSystem.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class SceneNodeAnimationsSystem;
	}
}

class Venator::GameObjectComponentSystem::SceneNodeAnimationsSystem : public BaseSystem {
	public:		
		SceneNodeAnimationsSystem(void);
		~SceneNodeAnimationsSystem(void);			

		void update(Component* c);
		void enter();
		void exit();
					
};


#endif