

#include "ComponentSpeed.h"
#include "../GameObject.h"
#include "../../utils/VenatorUtils.h"



using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


Factory<Component,ComponentSpeed> ComponentSpeed::compFactory;

ComponentSpeed::ComponentSpeed(void) :  	
									Component("speed"),
									max_front_speed(0),
									rotation_speed(0),
									current_speed(0)
{}


ComponentSpeed::~ComponentSpeed(void) 
{}


void ComponentSpeed::start() 
{
	PARAMETERSMAP::iterator it = owner->parameters.find("max_front_speed");
	if (it != owner->parameters.end()) {
		max_front_speed = Utils::String2Number<Scalar>((*it).second);
	}
	it = owner->parameters.find("rotation_speed");
	if (it != owner->parameters.end()) {
		rotation_speed = Utils::String2Number<Scalar>((*it).second);
	}	
	it = owner->parameters.find("initial_speed");
	if (it != owner->parameters.end()) {
		current_speed = Utils::String2Number<Scalar>((*it).second);
	}
}

