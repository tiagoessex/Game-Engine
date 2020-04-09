
/**

	PARAMETERS:
		- [meshanimationstart]	- initial animation state name
		- [meshanimationloop]	- 

	DEPENDENCIES:
		- ComponentEntity
			- ATT: entity must exist


	
*/

#ifndef __ComponentMeshAnimation_H__
#define __ComponentMeshAnimation_H__

#include "Component.h"


namespace Venator {	namespace GameObjectComponentSystem	{ class ComponentMeshAnimation;} }

namespace Ogre { 
	class AnimationState; 
	class Entity;
}

class Venator::GameObjectComponentSystem::ComponentMeshAnimation : public Component 
{
	private:
		Ogre::AnimationState* animationstate;
		Ogre::Entity* entity;
		std::string empty;

	public:
		ComponentMeshAnimation(void);
		~ComponentMeshAnimation(void);			

		void start();

		const std::string& getCurrentAnimationName(void);
		void setAnimation(const std::string& animationname, bool loop = true);
		Ogre::AnimationState* getAnimationState(void) { return animationstate; }

		static Factory<Component,ComponentMeshAnimation> compFactory;

};



#endif