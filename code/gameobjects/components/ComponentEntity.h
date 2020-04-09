
/**

	PARAMETERS:
		- [mesh]	- mesh filename

	DEPENDENCIES:
		- ComponentRender 
			- ATT: node and manager must already be defined
	
*/


#ifndef __ComponentEntity_H__
#define __ComponentEntity_H__

#include "Component.h"


namespace Ogre {
	class Entity;
}

namespace Venator {	
	namespace GameObjectComponentSystem	{
		class ComponentEntity;
	}
}

class Venator::GameObjectComponentSystem::ComponentEntity : public Component {
	private:
		Ogre::Entity* entity;
		std::string meshfile;
		void _start();

	public:
		ComponentEntity(void);
		~ComponentEntity(void);			

		void start();
		void end();		

		void setEntity(Ogre::Entity* ent);
		Ogre::Entity* getEntity(void) const;
		void setVisible(bool b);
		bool isVisible(void);
		void setCastShadows(bool b);

		const std::string& getMeshFile(void) { return meshfile; }
		void setMeshFile(const std::string& file) { meshfile = file; }

		static Factory<Component,ComponentEntity> compFactory;

};



#endif