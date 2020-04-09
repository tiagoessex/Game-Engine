
/**

	PARAMETERS:
	
	DEPEDENCIES:
	
	
*/


#ifndef __ComponentCollisions_H__
#define __ComponentCollisions_H__

#include "Component.h"
//#include "../../Prerequisites.h"


namespace Venator {	
	namespace GameObjectComponentSystem {
		class ComponentCollisions;
	}
}
class Venator::GameObjectComponentSystem::ComponentCollisions : public Component {

	public:
		ComponentCollisions(void) : Component("collisions") {};
		~ComponentCollisions(void) {};

		static Factory<Component,ComponentCollisions> compFactory;

};


#endif