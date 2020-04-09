

#include "ExplosionSystem.h"
#include "../World.h"
#include "../components/ComponentExplosion.h"
#include "../../Globals.h"


#include "OgreSceneManager.h"
#include "OgreSceneNode.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


// can have delta - must check exp status every frame
ExplosionSystem::ExplosionSystem(void) : BaseSystem("ExplosionSystem")
{
	LOGTORS("************ ExplosionSystem CTOR ************");	
}
	
ExplosionSystem::~ExplosionSystem(void) {
	LOGTORS("************ ExplosionSystem DTOR ************");
}


void ExplosionSystem::enter() {
	LOGINFO("[ExplosionSystem::enter] ExplosionSystem enter");	
	handleComponent("explosion");	
}

void ExplosionSystem::update(Component* go) {
	ComponentExplosion* c_exp = 0;
	c_exp = static_cast<ComponentExplosion*> (go);

	if (c_exp->getTextureUnitState()->getCurrentFrame() == c_exp->getTextureUnitState()->getNumFrames()-1) {
		World::getInstance()->deleteGameObject(c_exp->getOwner());
	}
	
}

void ExplosionSystem::exit() {
	LOGINFO("[ExplosionSystem::exit] ExplosionSystem exit");
}
