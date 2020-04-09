
/**
	base class for all components
		- all components should be created/destroyed by the componentsfactory thorugh the world/go
		- it is possible to create components outside componentsfactory but it is not advisable 
		- components should be (if possible) only for data holding and set/get methods
		- start()/end() were added as a convenience - the are used to instantiate/create/dispose required objects
			and to do cleanups of these instantiations
			start() - called by world when is component is created
			end() - called by componentsfactory when component is destroyed
			
			e.g.: mesh is created and destroyed by the component => requires rendercomponents for the manager
			e.g.: render with node requires the transform components to set node

			*** USING START()/END() NOT GOOD, BUT SIMPLIFIES A LOT
		- when component is added to a go => start() is called
		- when component is removed from a go => end() is called	

	ATT: 
		- after component creation and set it to a go or world - DO NOT CALL DELETE

*/

#ifndef __Component_H__
#define __Component_H__


#include "../GameObjectCommon.h"
#include "../ComponentsFactories.h"

namespace Venator {
	namespace GameObjectComponentSystem {
		class GameObject;
		class World;
		class Component;
	}
}

class Venator::GameObjectComponentSystem::Component {
	protected:
		bool enabled;			// component enabled - ready to be operated
								// useful when refresh (avoids init duplication)
		std::string type;		// component unique name id
		CPOS typenumber;		// component unique type ID
		GameObject* owner;
		
	public:
		Component(const std::string& type);
		virtual ~Component();

		const std::string& getType(void) const { return type; };
		CPOS getComponentTypeID(void) const { return typenumber; };

		void setOwner(GameObject* id) { owner = id; };
		GameObject* getOwner(void) { return owner; };			
		
		void setEnable(bool e) { enabled = e; };
		bool isEnable(void) const { return enabled; };

		
		virtual void start(void) {};
		virtual void end(void) {};

		typedef ComponentsBaseFactory<Component> CompBaseFactory;

};	// class component


#endif
