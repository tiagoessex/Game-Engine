

/**

*/


#ifndef __MeshAnimationsSystem_H__
#define __MeshAnimationsSystem_H__


#include "BaseSystem.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class MeshAnimationsSystem;
	}
}

class Venator::GameObjectComponentSystem::MeshAnimationsSystem : public BaseSystem {
	public:		
		MeshAnimationsSystem(void);
		~MeshAnimationsSystem(void);			

		void update(Component* c);
		void enter();
		void exit();
					
};


#endif