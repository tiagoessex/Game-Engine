

#include "SoundListenerSystem.h"
#include "../GameObject.h"
#include "../components/ComponentSoundListener.h"
#include "../components/ComponentPosition.h"
#include "../World.h"

#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"
#include "../../sound/SoundListener.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



SoundListenerSystem::SoundListenerSystem(void) : BaseSystem("SoundListenerSystem", false, 0.5)
{
	LOGTORS("************ SoundListenerSystem CTOR ************");	
}
	
SoundListenerSystem::~SoundListenerSystem(void) {
	LOGTORS("************ SoundListenerSystem DTOR ************");
}


void SoundListenerSystem::enter() {
	LOGINFO("[SoundListenerSystem::enter] SoundListenerSystem enter");	
	handleComponent("soundlistener");
}

void SoundListenerSystem::update(Component* c) {
	ComponentSoundListener* c_list = 0;
	c_list = static_cast<ComponentSoundListener*> (c);
	ComponentPosition* c_pos = 0;
	c_pos = static_cast<ComponentPosition*> (c->getOwner()->getComponent(POSITION));
	c_list->getListener()->setPosition(c_pos->position);
}

void SoundListenerSystem::exit() {
	LOGINFO("[SoundListenerSystem::exit] SoundListenerSystem exit");
}
