

#include "ComponentMeshAnimation.h"
#include "ComponentEntity.h"
#include "../GameObject.h"

#include "OgreEntity.h"

//#include "../../Globals.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



Factory<Component,ComponentMeshAnimation> ComponentMeshAnimation::compFactory;


ComponentMeshAnimation::ComponentMeshAnimation(void) :  
							Component("meshanimation"),
							animationstate(0),
							entity(0)

					
{}


ComponentMeshAnimation::~ComponentMeshAnimation(void) {}


void ComponentMeshAnimation::start() 
{
	std::string loop = "true";
	PARAMETERSMAP::iterator it1 = owner->parameters.find("meshanimationstart");
	if (it1 == owner->parameters.end()) { return; }
	std::string animationname = (*it1).second;
	it1 = owner->parameters.find("meshanimationloop");
	if (it1 != owner->parameters.end()) { loop = (*it1).second; }


	ComponentEntity* c_entity = static_cast<ComponentEntity*> (getOwner()->getComponent(ENTITY));
	if (c_entity) {
		entity = c_entity->getEntity();
		if (entity && entity->hasAnimationState(animationname)) {
			animationstate = entity->getAnimationState(animationname);
			animationstate->setEnabled(true);
			if (loop == "true") { animationstate->setLoop(true); }
			else { animationstate->setLoop(false); }			
		}/* else {
			LOGERROR("ComponentMeshAnimation ERROR");
		}*/
	}	
}




const std::string& ComponentMeshAnimation::getCurrentAnimationName(void)
{ 
	if (animationstate) { return animationstate->getAnimationName(); }
	else { return empty; }
}

void ComponentMeshAnimation::setAnimation(const std::string& animationname, bool loop)
{
	if (animationstate && entity) { 
		if (entity->hasAnimationState(animationname)) {
			animationstate = entity->getAnimationState(animationname);
			animationstate->setEnabled(true);
			animationstate->setLoop(loop);
		}
	}
}
