
/**

	PARAMETERS:
		- [scenenodeanimation]	- name defined in animations.xml and set
								in RenderEngine::SceneNodeAnimManager

	DEPENDENCIES:
		- ComponentRender 
			- ATT: node must already be defined
		- animations already loaded (by RenderEngine::SceneNodeAnimManager
			through RenderEngine::RenderManager)

	ATT:
		- all position/scale/orientations changes should be done by the SceneNodeAnimationsSystem
			=> can not be handle by renderXXXXsystem / FowardMovementSystem / ...

	
*/


#ifndef __ComponentSceneNodeAnimation_H__
#define __ComponentSceneNodeAnimation_H__

#include "Component.h"


namespace Venator {	
	namespace GameObjectComponentSystem	{ class ComponentSceneNodeAnimation;}
	namespace RenderEngine { struct NodeAnimation; }
}

class Venator::GameObjectComponentSystem::ComponentSceneNodeAnimation : public Component {
	private:
		Venator::RenderEngine::NodeAnimation* animation;
		
	public:
		ComponentSceneNodeAnimation(void);
		~ComponentSceneNodeAnimation(void);			

		void start();

		const std::string& getAnimationName(void);
		void setAnimation(const std::string&);
		Venator::RenderEngine::NodeAnimation* getAnimation(void) { return animation; }

		static Factory<Component,ComponentSceneNodeAnimation> compFactory;

};



#endif