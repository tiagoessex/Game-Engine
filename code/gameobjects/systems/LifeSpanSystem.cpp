

#include "LifeSpanSystem.h"
#include "../GameObject.h"
#include "../components/ComponentLifeSpan.h"
#include "../World.h"

#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"



using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



LifeSpanSystem::LifeSpanSystem(void) : BaseSystem("LifeSpanSystem")
{
	LOGTORS("************ LifeSpanSystem CTOR ************");	
}
	
LifeSpanSystem::~LifeSpanSystem(void) {
	LOGTORS("************ LifeSpanSystem DTOR ************");
}


void LifeSpanSystem::enter() {
	LOGINFO("[LifeSpanSystem::enter] LifeSpanSystem enter");	
	handleComponent("lifespan");
}

void LifeSpanSystem::update(Component* c) {
	ComponentLifeSpan* life = 0;
	life = static_cast<ComponentLifeSpan*> (c);
	life->current_life += World::getInstance()->getDelta();
	if (life->current_life > life->lifespan) {
		World::getInstance()->deleteGameObject(c->getOwner());
	}
}

void LifeSpanSystem::exit() {
	LOGINFO("[LifeSpanSystem::exit] LifeSpanSystem exit");
}
