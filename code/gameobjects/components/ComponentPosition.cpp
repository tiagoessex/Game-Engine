



#include "ComponentPosition.h"
#include "../GameObject.h"
#include "../../utils/VenatorUtils.h"


using namespace Venator::GameObjectComponentSystem;

Factory<Component,ComponentPosition> ComponentPosition::compFactory;


void ComponentPosition::start(void) 
{
	PARAMETERSMAP::iterator it = owner->parameters.find("position");
	if (it == owner->parameters.end()) { return; }	
	position = Utils::String2Vec3((*it).second);	
}

