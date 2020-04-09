

/**
		system for tests: go handling (3 components handling)
*/


#ifndef __RenderPositionSystem_H__
#define __RenderPositionSystem_H__


#include "BaseSystem.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class RenderPositionSystem;
	}
}

class Venator::GameObjectComponentSystem::RenderPositionSystem : public BaseSystem {
	public:		
		RenderPositionSystem(void);
		~RenderPositionSystem(void);			

		void update(GameObject* go);	// each go - called by _updateSystem
		void enter();				// called by systemsmanager during system init
		void exit();					// called by systemsmanager during system finalizing
						
};		// class RenderPositionSystem


#endif