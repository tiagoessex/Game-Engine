
/**

	PARAMETERS:
		- [material]	- explosion material

	DEPENDENCIES:
		- ComponentRender 
			- ATT: node and manager must already be defined
	
*/


#ifndef __ComponentExplosion_H__
#define __ComponentExplosion_H__

#include "Component.h"

#include "OgreMaterial.h"

namespace Ogre {
	class Billboard;
	class SceneManager;
}

namespace Venator {	
	namespace GameObjectComponentSystem	{
		class ComponentExplosion;
	}
}

class Venator::GameObjectComponentSystem::ComponentExplosion : public Component {
	private:
		int id;	
		std::string name;
		Ogre::Billboard* myBillboard;
		Ogre::TextureUnitState* texture_unit_state;
		Ogre::MaterialPtr mat2;
		Ogre::BillboardSet* set;
		Ogre::MaterialPtr mat;
		Ogre::SceneManager* manager;

		static int ID;
		
	public:
		ComponentExplosion(void);
		~ComponentExplosion(void);			

		void start();
		void end();

		Ogre::TextureUnitState* getTextureUnitState(void) { return texture_unit_state; };

		static Factory<Component,ComponentExplosion> compFactory;

};



#endif