
/**

	PARAMETERS:
		- [sound_name]
		- [sound_loop]		- (optional)
		- [sound_volume]	- (optional)
		- [sound_pan]		- (optional)

*/


#ifndef __ComponentSound2D_H__
#define __ComponentSound2D_H__

#include "Component.h"



namespace Venator {	
	namespace SoundSystem {
		class Sound;
	}
}

namespace Venator {
	namespace GameObjectComponentSystem	{
		class ComponentSound2D;
	}
}


class Venator::GameObjectComponentSystem::ComponentSound2D : public Component 
{
	private:
		Venator::SoundSystem::Sound* sound;		

	public:
		ComponentSound2D(void);
		~ComponentSound2D(void);
		
		void start();
		void end();

		Venator::SoundSystem::Sound* getSound2D(void) { return sound; }

		static Factory<Component,ComponentSound2D> compFactory;

};



#endif
