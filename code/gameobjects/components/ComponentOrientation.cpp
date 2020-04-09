



#include "ComponentOrientation.h"
#include "../GameObject.h"
#include "../../utils/VenatorUtils.h"


using namespace Venator::GameObjectComponentSystem;


Factory<Component,ComponentOrientation> ComponentOrientation::compFactory;

void ComponentOrientation::start(void) 
{
	PARAMETERSMAP::iterator it = owner->parameters.find("orientation");
	if (it == owner->parameters.end()) { return; }	
	orientation = Utils::String2Quat((*it).second);
}