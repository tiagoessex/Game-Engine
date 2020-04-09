

#include "ComponentEntity.h"
//#include "../../renderengine/RenderManager.h"
#include "../GameObject.h"
#include "ComponentRender.h"


#include "OgreEntity.h"
#include "OgreSceneManager.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
//using namespace Venator::RenderEngine;


Factory<Component,ComponentEntity> ComponentEntity::compFactory;


ComponentEntity::ComponentEntity(void) :  
							Component("entity"),
							entity(0)
					
{}


ComponentEntity::~ComponentEntity(void) {}


void ComponentEntity::start() 
{
	PARAMETERSMAP::iterator it1 = owner->parameters.find("mesh");
	if (it1 == owner->parameters.end()) { return; }
	meshfile = (*it1).second;
	
	_start();
	
}


void ComponentEntity::_start() 
{	
	ComponentRender* c_render = static_cast<ComponentRender*> (getOwner()->getComponent(RENDER));
	if (c_render) {
		Ogre::SceneManager* manager = c_render->getSceneManager();
		Ogre::SceneNode* node = c_render->getSceneNode();
		if (manager && node) {
		//	entity = RenderManager::getInstance()->createEntity
		//		(meshfile, manager, node);
			entity = manager->createEntity(meshfile);
			node->attachObject(entity);	
		}
	}	
}

void ComponentEntity::end() 
{
	if (!entity) {
		return;
	}

	//Venator::RenderEngine::RenderManager::getInstance()->destroyEntity(entity);

	if (entity->isAttached()) {
		entity->getParentSceneNode()->detachObject(entity);
	}
	entity->_getManager()->destroyEntity(entity);

}


void ComponentEntity::setEntity(Ogre::Entity* ent) 
{
	entity = ent;
	_start();
}

Ogre::Entity* ComponentEntity::getEntity(void) const 
{
	return entity;
}

void ComponentEntity::setVisible(bool b) 
{
	if (entity) {
		entity->setVisible(b);
	}
}

bool ComponentEntity::isVisible(void) 
{
	if (entity) {
		return entity->isVisible();
	}
	return false;
}

void ComponentEntity::setCastShadows(bool b) 
{
	if (entity) {
		entity->setCastShadows(b);
	}
}
