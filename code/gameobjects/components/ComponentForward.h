
/**


*/


#ifndef __ComponentForward_H__
#define __ComponentForward_H__

#include "Component.h"


namespace Venator {	
	namespace GameObjectComponentSystem {
		class ComponentForward;
	}
}

class Venator::GameObjectComponentSystem::ComponentForward : public Component {
	public:
		ComponentForward(void) :  Component("forward") {};

		~ComponentForward(void) { };

		static Factory<Component,ComponentForward> compFactory;

};	// class ComponentForward



#endif