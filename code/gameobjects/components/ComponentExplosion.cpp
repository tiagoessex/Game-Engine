

#include "ComponentExplosion.h"
#include "../../renderengine/RenderManager.h"
#include "../GameObject.h"
#include "ComponentRender.h"
#include "../../utils/VenatorUtils.h"

#include <OgreStringConverter.h>
#include <OgreSceneNode.h>
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>
#include <OgreSceneManager.h>


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::RenderEngine;


Factory<Component,ComponentExplosion> ComponentExplosion::compFactory;

int ComponentExplosion::ID = 0;

ComponentExplosion::ComponentExplosion(void) :  
							Component("explosion"),
							id(ID),
							myBillboard(0),
							texture_unit_state(0),
							set(0),
							manager(0)
					
{
	ID++;
}


ComponentExplosion::~ComponentExplosion(void) {}


void ComponentExplosion::start() 
{
	std::string explosion_material;
	PARAMETERSMAP::iterator it1 = owner->parameters.find("material");
	if (it1 == owner->parameters.end()) { return; }
	explosion_material = (*it1).second;
	
	ComponentRender* c_render = static_cast<ComponentRender*> (getOwner()->getComponent(RENDER));
	if (!c_render) { return; }
	if (!c_render->getSceneManager() && !c_render->getSceneNode()) { return; }
	manager = c_render->getSceneManager();
	Ogre::SceneNode* node = c_render->getSceneNode();

	name = "ComponentExplosion_" + Utils::Number2String(id);
	set = manager->createBillboardSet(name);

	myBillboard = set->createBillboard(node->getPosition());// * 1/node->getScale());
	node->attachObject(set);

	// clone material
	Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName(explosion_material);
	mat2 = mat->clone(name);
	set->setMaterial(mat2);
	texture_unit_state = mat2->getTechnique(0)->getPass(0)->getTextureUnitState(0);	
}


void ComponentExplosion::end() 
{
	if (!myBillboard || !set) {
		return;
	}

	set->getParentSceneNode()->detachObject(set);	
	set->removeBillboard(myBillboard);
	manager->destroyBillboardSet(set);
	set = 0;
	myBillboard = 0;

	texture_unit_state = 0;	
	Ogre::MaterialManager::getSingleton().remove(mat2->getHandle());
	mat2.setNull();
}

