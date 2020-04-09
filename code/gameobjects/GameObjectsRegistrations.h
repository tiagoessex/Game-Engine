
/**
	new components should be registered here
	initial systems should also be here
*/

#ifndef __GameObjectsRegistration_H__
#define __GameObjectsRegistration_H__


namespace Venator { 
	namespace GameObjectComponentSystem {
		class World;
		class ComponentsFactory;

		void registerComponents(ComponentsFactory* cfactory);
		void registerSystems(World* world);

	}
}


#endif
