
/**

	PARAMETERS:
		- [sound_name]
		- [sound_loop]		- (optional)
		- [sound_volume]	- (optional)
		- [sound_pan]		- (optional)


	DEPENDENCIES
		- ComponentPosition		- (optional)


*/


#ifndef __ComponentSound3D_H__
#define __ComponentSound3D_H__

#include "Component.h"


namespace Venator {	
	namespace SoundSystem {
		class Sound3D;
	}
}

namespace Venator {
	namespace GameObjectComponentSystem	{
		class ComponentSound3D;
	}
}


class Venator::GameObjectComponentSystem::ComponentSound3D : public Component 
{
	private:
		Venator::SoundSystem::Sound3D* sound;	

	public:
		ComponentSound3D(void);
		~ComponentSound3D(void);
		
		void start();		
		void end();

		Venator::SoundSystem::Sound3D* getSound(void) { return sound; }

		static Factory<Component,ComponentSound3D> compFactory;

};



#endif
