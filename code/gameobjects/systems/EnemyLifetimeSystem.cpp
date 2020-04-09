

#include "EnemyLifetimeSystem.h"
#include "../GameObject.h"
#include "../components/ComponentPosition.h"
#include "../components/ComponentPlayerShootLifetime.h"
#include "../World.h"

#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"



using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



EnemyLifetimeSystem::EnemyLifetimeSystem(void) : 
		BaseSystem("EnemyLifetimeSystem", false, 0.2f)
{
	LOGTORS("************ EnemyLifetimeSystem CTOR ************");	
}
	
EnemyLifetimeSystem::~EnemyLifetimeSystem(void) {
	LOGTORS("************ EnemyLifetimeSystem DTOR ************");
}


void EnemyLifetimeSystem::enter() {
	LOGINFO("[EnemyLifetimeSystem::enter] EnemyLifetimeSystem enter");	
	handleComponent("enemylifetime");
	handleComponent("position");
}

void EnemyLifetimeSystem::update(GameObject* c) {
	ComponentPosition* pos = 0;
	pos = static_cast<ComponentPosition*> (c->getComponent(POSITION));
	if (pos->position.z > 30) {	
		World::getInstance()->deleteGameObject(c);
	}
}

void EnemyLifetimeSystem::exit() {
	LOGINFO("[EnemyLifetimeSystem::exit] EnemyLifetimeSystem exit");
}
