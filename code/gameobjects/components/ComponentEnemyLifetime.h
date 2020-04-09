
/**


	PARAMETERS:
			
*/


#ifndef __ComponentEnemyLifetime_H__
#define __ComponentEnemyLifetime_H__

#include "Component.h"
//#include "../../Prerequisites.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class ComponentEnemyLifetime;
	}
}


class Venator::GameObjectComponentSystem::ComponentEnemyLifetime : public Component {

	public:
		ComponentEnemyLifetime(void) :	Component("enemylifetime") {};
		~ComponentEnemyLifetime(void) {};


		static Factory<Component,ComponentEnemyLifetime> compFactory;

};



#endif
