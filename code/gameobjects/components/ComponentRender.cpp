

#include "ComponentRender.h"
#include "ComponentPosition.h"
#include "ComponentScale.h"
#include "ComponentOrientation.h"
#include "../GameObject.h"
#include "../../Prerequisites.h"
#include "../../renderengine/RenderManager.h"
#include "../../utils/VenatorUtils.h"
#include "../../renderengine/RenderUtils.h"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"

#include "../../Globals.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::RenderEngine;

Factory<Component,ComponentRender> ComponentRender::compFactory;

ComponentRender::ComponentRender(void) :  	
									Component("render"),
									manager(0),
									node(0)
{ }


ComponentRender::~ComponentRender(void) 
{ }


void ComponentRender::start() 
{
	PARAMETERSMAP::iterator it;
	std::string name = "";
	it = owner->parameters.find("name");
	if (it != owner->parameters.end()) { name = (*it).second; }

	it = owner->parameters.find("manager");
	if (it == owner->parameters.end()) { return; }
	std::string mgr = (*it).second;
	manager = RenderManager::getInstance()->getSceneManager(mgr);

	if (!manager) { return; }

	it = owner->parameters.find("parent");
	if (it == owner->parameters.end()) { 
		if (name == "") 
			{ node = manager->createSceneNode(); }
		else 
			{ node = manager->createSceneNode(name); }
	} else {
		std::string parent = (*it).second;
		//node = RenderManager::getInstance()->createNode(manager,manager->getSceneNode(parent));
		if (name == "") 
			{ node = manager->getSceneNode(parent)->createChildSceneNode(); }
		else 
			{ node = manager->getSceneNode(parent)->createChildSceneNode(name); }
	}

	if (!node) { return; }

	_start();
}


void ComponentRender::_start() 
{
	ComponentPosition* pos = static_cast<ComponentPosition*>(owner->getComponent(POSITION));
	if (pos) {
		node->setPosition(pos->getPosition());
	}

	ComponentScale* sc = static_cast<ComponentScale*>(owner->getComponent(SCALE));
	if (sc) {
		node->setScale(sc->getScale());
	}

	ComponentOrientation* ori = static_cast<ComponentOrientation*>(owner->getComponent(ORIENTATION));
	if (ori) {
		node->setOrientation(ori->getOrientation());
	}
}

void ComponentRender::end() 
{	
	if (node) {
		//Venator::RenderEngine::RenderManager::getInstance()->destroyNode(node);
		Venator::RenderEngine::clearSceneNode(node);
	}
}


Ogre::SceneManager* ComponentRender::getSceneManager(void) 
{
	return manager;
}

Ogre::SceneNode* ComponentRender::getSceneNode(void) 
{
	return node;
}

void ComponentRender::setSceneManager(Ogre::SceneManager* m) 
{
	manager = m;
	if (node) { _start(); }
}

void ComponentRender::setSceneNode(Ogre::SceneNode* n) 
{
	node = n;
	if (manager) { _start(); }
}

void ComponentRender::setVisibility(bool b) 
{
	node->setVisible(b);
}

void ComponentRender::attachTo(Ogre::SceneNode* m) 
{
	if (node->getParentSceneNode() != m) {		
		m->addChild(node);
	}
}

void ComponentRender::detach(void) 
{
	node->getParentSceneNode()->removeChild(node);
}