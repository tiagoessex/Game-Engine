
/**
	solely responsable in creating/destroying components

	when destroy => calls component::end() + dtor
*/


#ifndef __ComponentsFactory_h_
#define __ComponentsFactory_h_



#include <map>

#include "ComponentsFactories.h"
#include "components/Component.h"


namespace Venator {
	namespace GameObjectComponentSystem {
		class ComponentsFactory;
	}
}


class Venator::GameObjectComponentSystem::ComponentsFactory {		
	public:					
		void initialise(void);
		void destroy(void);
		void reset(void);	

		void registerComponent(const std::string& name, CPOS id, Component::CompBaseFactory* f);
		void unregisterComponent(const std::string& name);
		Component* createComponent(const std::string& name);
		void destroyComponent(Component* c);
		
		CPOS getComponentTypeID(const std::string& name);
		std::map<std::string, CPOS > componentsIDMap;

		static ComponentsFactory* getInstance( void );
	private:	
		ComponentsFactory(void);
		~ComponentsFactory(void);
		ComponentsFactory( const ComponentsFactory& ) { }
		ComponentsFactory & operator = ( const ComponentsFactory& );
		static ComponentsFactory *mComponentsFactory;	


		std::map<std::string,Component::CompBaseFactory *>  factories;		
		

};	// class ComponentsFactory




#endif
