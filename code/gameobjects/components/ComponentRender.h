
/**
		render component - manager and node

		ATT: do not use rootscenenode as parent

	PARAMETERS:
		- [manager]
		- [parent]		- => create child node

	DEPENDENCIES
		- ComponentPosition		- (optional)
		- ComponentScale		- (optional)
		- ComponentOrientation	- (optional)
*/


#ifndef __ComponentRender_H__
#define __ComponentRender_H__

#include "Component.h"


namespace Ogre {
	class SceneManager;
	class SceneNode;
}

namespace Venator {
	namespace GameObjectComponentSystem	{
		class ComponentRender;
	}
}


class Venator::GameObjectComponentSystem::ComponentRender : public Component {
	
	private:
		Ogre::SceneManager* manager;
		Ogre::SceneNode* node;
		void _start();

	public:
		ComponentRender(void);
		~ComponentRender(void);		
		
		void start();
		void end();

		Ogre::SceneManager* getSceneManager(void);
		Ogre::SceneNode* getSceneNode(void);
		void setSceneManager(Ogre::SceneManager* m);
		void setSceneNode(Ogre::SceneNode* n);

		void setVisibility(bool b);

		void attachTo(Ogre::SceneNode* m);
		void detach(void);

		static Factory<Component,ComponentRender> compFactory;

};



#endif
