

#include "ComponentScale.h"
#include "../GameObject.h"
#include "../../utils/VenatorUtils.h"



using namespace Venator::GameObjectComponentSystem;


Factory<Component,ComponentScale> ComponentScale::compFactory;

void ComponentScale::start() 
{
	PARAMETERSMAP::iterator it = owner->parameters.find("scale");
	if (it == owner->parameters.end()) { return; }
	scale = Utils::String2Vec3((*it).second);
}