

/**

*/


#ifndef __SoundListenerSystem_H__
#define __SoundListenerSystem_H__


#include "BaseSystem.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class SoundListenerSystem;
	}
}

class Venator::GameObjectComponentSystem::SoundListenerSystem : public BaseSystem {
	public:		
		SoundListenerSystem(void);
		~SoundListenerSystem(void);

		void update(Component* c);
		void enter();
		void exit();
						
};


#endif