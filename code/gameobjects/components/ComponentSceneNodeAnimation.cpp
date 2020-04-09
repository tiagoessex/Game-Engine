

#include "ComponentSceneNodeAnimation.h"
#include "ComponentRender.h"
#include "../GameObject.h"
#include "../../renderengine/RenderManager.h"
#include "../../renderengine/NodeAnimation.h"


//#include "ComponentPosition.h"
//#include "ComponentScale.h"
//#include "ComponentOrientation.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::RenderEngine;


Factory<Component,ComponentSceneNodeAnimation> ComponentSceneNodeAnimation::compFactory;


ComponentSceneNodeAnimation::ComponentSceneNodeAnimation(void) :  
							Component("scenenodeanimation"),
							animation(0)
					
{}


ComponentSceneNodeAnimation::~ComponentSceneNodeAnimation(void) {}


void ComponentSceneNodeAnimation::start() 
{
	PARAMETERSMAP::iterator it1 = owner->parameters.find("scenenodeanimation");
	if (it1 == owner->parameters.end()) { return; }
	std::string animationname = (*it1).second;

	ComponentRender* c_render = static_cast<ComponentRender*> (getOwner()->getComponent(RENDER));
	if (c_render) {
		Ogre::SceneNode* node = c_render->getSceneNode();
		if (node) {
			animation = RenderManager::getInstance()->getNodeAnimation(animationname);
			if (animation) { animation->setNode(node); } 
		}
	}	
}




const std::string& ComponentSceneNodeAnimation::getAnimationName(void)
{ 
	// need check
	return animation->getAnimation()->getName(); 
}


void ComponentSceneNodeAnimation::setAnimation(const std::string& animationname)
{
	ComponentRender* c_render = static_cast<ComponentRender*> (getOwner()->getComponent(RENDER));
	if (c_render) {
		Ogre::SceneNode* node = c_render->getSceneNode();
		if (node) {
			animation = RenderManager::getInstance()->getNodeAnimation(animationname);
			if (animation) { animation->setNode(node); } 
		}
	}
}