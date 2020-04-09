
/**


	PARAMETERS:
		[listener_lookdir]	- Vec3(0,0,1) - (optional)
		[velocity]			- Vec3(0,0,0) - (optional)
		[listener_upvector]	- Vec3(0,1,0) - (optional)


	DEPENDENCIES
		- ComponentPosition
*/


#ifndef __ComponentSoundListener_H__
#define __ComponentSoundListener_H__

#include "Component.h"

namespace Venator {	
	namespace SoundSystem {
		class SoundListener;
	}
}

namespace Venator {
	namespace GameObjectComponentSystem	{
		class ComponentSoundListener;
	}
}


class Venator::GameObjectComponentSystem::ComponentSoundListener : public Component 
{
	private:
		Venator::SoundSystem::SoundListener* listener;
	public:
		ComponentSoundListener(void);
		~ComponentSoundListener(void);
		
		void start();		
		void end();

		Venator::SoundSystem::SoundListener* getListener(void) { return listener; }

		static Factory<Component,ComponentSoundListener> compFactory;

};



#endif
