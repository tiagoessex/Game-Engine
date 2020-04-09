

#include "ComponentSound3D.h"
#include "ComponentPosition.h"
#include "../GameObject.h"
#include "../../utils/VenatorUtils.h"
#include "../../sound/SoundManager.h"
#include "ComponentPosition.h"
#include "../../sound/Sound3D.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::SoundSystem;

Factory<Component,ComponentSound3D> ComponentSound3D::compFactory;

ComponentSound3D::ComponentSound3D(void) :  	
									Component("sound3d")
{}


ComponentSound3D::~ComponentSound3D(void) 
{}


void ComponentSound3D::start()
{
	bool sound_loop = false;
	Scalar sound_volume = 0.75f;
	Scalar sound_pan = 0.0f;
	std::string sound_name;
	Vec3 pos(0,0,0);

	PARAMETERSMAP::iterator it = owner->parameters.find("sound_name");
	if (it == owner->parameters.end()) { return; }
	sound_name = (*it).second;
	
	it = owner->parameters.find("sound_loop");
	if (it != owner->parameters.end()) {
		if ((*it).second == "true") { sound_loop = true; }
		else { sound_loop = false; }
	}
	it = owner->parameters.find("sound_volume");
	if (it != owner->parameters.end()) {
		sound_volume = Utils::String2Number<Scalar>((*it).second);
	}	
	it = owner->parameters.find("sound_pan");
	if (it != owner->parameters.end()) {
		sound_pan = Utils::String2Number<Scalar>((*it).second);
	}

	ComponentPosition* c_pos = static_cast<ComponentPosition*> (getOwner()->getComponent(POSITION));
	if (c_pos) {
		pos = c_pos->getPosition();
	}

	sound = SoundManager::getInstance()->createSound3D(sound_name.c_str(), pos, sound_loop, sound_volume, sound_pan);	
	sound->play();
}


void ComponentSound3D::end() 
{
	if (!sound) { return; }
	SoundManager::getInstance()->destroySound((Sound*) (sound));
}