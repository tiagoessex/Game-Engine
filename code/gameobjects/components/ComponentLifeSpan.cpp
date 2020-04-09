

#include "ComponentLifeSpan.h"
#include "../GameObject.h"
#include "../../utils/VenatorUtils.h"



using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


Factory<Component,ComponentLifeSpan> ComponentLifeSpan::compFactory;

ComponentLifeSpan::ComponentLifeSpan(void) :  	
									Component("lifespan"),
									current_life(0),
									lifespan(0)
{}


ComponentLifeSpan::~ComponentLifeSpan(void) 
{}


void ComponentLifeSpan::start() 
{
	PARAMETERSMAP::iterator it = owner->parameters.find("lifespan");
	if (it == owner->parameters.end()) { return; }
	lifespan = Utils::String2Number<Scalar>((*it).second);		
}

