
/**

	player control

	PARAMETERS:


	DEPEDENCIES:
	
	
*/


#ifndef __ComponentPlayerControl_H__
#define __ComponentPlayerControl_H__

#include "Component.h"


namespace Venator {	
	namespace GameObjectComponentSystem {
		class ComponentPlayerControl;
	}
}
class Venator::GameObjectComponentSystem::ComponentPlayerControl : public Component {

	public:
		ComponentPlayerControl(void) : Component("playercontrol") {};
		~ComponentPlayerControl(void) {};

		static Factory<Component,ComponentPlayerControl> compFactory;

};	// class ComponentPlayerControl


#endif