

#include "PlayerShootLifetimeSystem.h"
#include "../GameObject.h"
#include "../components/ComponentPosition.h"
#include "../components/ComponentPlayerShootLifetime.h"
#include "../World.h"

#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"



using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



PlayerShootLifetimeSystem::PlayerShootLifetimeSystem(void) : 
		BaseSystem("PlayerShootLifetimeSystem", false, 0.2f)
{
	LOGTORS("************ PlayerShootLifetimeSystem CTOR ************");	
}
	
PlayerShootLifetimeSystem::~PlayerShootLifetimeSystem(void) {
	LOGTORS("************ PlayerShootLifetimeSystem DTOR ************");
}


void PlayerShootLifetimeSystem::enter() {
	LOGINFO("[PlayerShootLifetimeSystem::enter] PlayerShootLifetimeSystem enter");	
	handleComponent("playershootlifetime");
	handleComponent("position");
}

void PlayerShootLifetimeSystem::update(GameObject* c) {
	ComponentPosition* pos = 0;
	pos = static_cast<ComponentPosition*> (c->getComponent(POSITION));
	if (pos->position.z < -30) {	
		World::getInstance()->deleteGameObject(c);
	}
}

void PlayerShootLifetimeSystem::exit() {
	LOGINFO("[PlayerShootLifetimeSystem::exit] PlayerShootLifetimeSystem exit");
}
