

/**

*/


#ifndef __LifeSpanSystem_H__
#define __LifeSpanSystem_H__


#include "BaseSystem.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class LifeSpanSystem;
	}
}

class Venator::GameObjectComponentSystem::LifeSpanSystem : public BaseSystem {
	public:		
		LifeSpanSystem(void);
		~LifeSpanSystem(void);			

		void update(Component* c);	// each go - called by _updateSystem
		void enter();				// called by systemsmanager during system init
		void exit();					// called by systemsmanager during system finalizing
						
};		// class LifeSpanSystem


#endif