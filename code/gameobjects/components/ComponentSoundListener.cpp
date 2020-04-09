

#include "ComponentSoundListener.h"
#include "ComponentPosition.h"
#include "../GameObject.h"
#include "../../utils/VenatorUtils.h"
#include "../../sound/SoundManager.h"
#include "../../sound/SoundListener.h"
#include "ComponentPosition.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::SoundSystem;

Factory<Component,ComponentSoundListener> ComponentSoundListener::compFactory;

ComponentSoundListener::ComponentSoundListener(void) :  	
									Component("soundlistener"),
									listener(0)
{}


ComponentSoundListener::~ComponentSoundListener(void) 
{}


void ComponentSoundListener::start()
{
	Vec3 pos(0,0,0);
	Vec3 lookdir(0,0,1);
	Vec3 velocity(0,0,0);
	Vec3 upvector(0,1,0);


	ComponentPosition* c_pos = static_cast<ComponentPosition*>(owner->getComponent(POSITION));
	if (c_pos) {
		pos = c_pos->getPosition();
	}


	PARAMETERSMAP::iterator it = owner->parameters.find("velocity");
	if (it != owner->parameters.end()) {
		velocity = Utils::String2Vec3((*it).second);
	}

	it = owner->parameters.find("listener_lookdir");
	if (it != owner->parameters.end()) {
		lookdir = Utils::String2Vec3((*it).second);
	}

	it = owner->parameters.find("listener_upvector");
	if (it != owner->parameters.end()) {
		upvector = Utils::String2Vec3((*it).second);
	}

	listener = SoundManager::getInstance()->createListener(pos, lookdir, velocity, upvector);
}


void ComponentSoundListener::end() 
{
	// listener deleted in soundmanager
}
