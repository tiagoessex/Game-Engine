

#include "ComponentSound2D.h"
#include "../GameObject.h"
#include "../../utils/VenatorUtils.h"
#include "../../sound/SoundManager.h"
#include "../../sound/Sound.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::SoundSystem;

Factory<Component,ComponentSound2D> ComponentSound2D::compFactory;

ComponentSound2D::ComponentSound2D(void) :  	
									Component("sound2d"),
									sound(0)
{}


ComponentSound2D::~ComponentSound2D(void) 
{}


void ComponentSound2D::start() 
{
	bool sound_loop = false;
	Scalar sound_volume = 0.75f;
	Scalar sound_pan = 0.0f;
	std::string sound_name;

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

	sound = SoundManager::getInstance()->createSound2D(sound_name.c_str(),sound_loop, sound_volume, sound_pan);	
	sound->play();
}

void ComponentSound2D::end() {
	if (!sound) { return; }
	SoundManager::getInstance()->destroySound(sound);
}