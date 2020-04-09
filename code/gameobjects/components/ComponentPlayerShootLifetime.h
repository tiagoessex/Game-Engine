
/**


	PARAMETERS:
			
*/


#ifndef __ComponentPlayerShootLifetime_H__
#define __ComponentPlayerShootLifetime_H__

#include "Component.h"
#include "../../Prerequisites.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class ComponentPlayerShootLifetime;
	}
}


class Venator::GameObjectComponentSystem::ComponentPlayerShootLifetime : public Component {

	public:
		ComponentPlayerShootLifetime(void) :	Component("playershootlifetime") {};
		~ComponentPlayerShootLifetime(void) {};


		static Factory<Component,ComponentPlayerShootLifetime> compFactory;

};



#endif
