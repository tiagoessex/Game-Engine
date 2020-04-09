

#include "Component.h"
#include "../World.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


Component::Component(const std::string& type) :
						enabled(false),
						type(type)
{
	// get the type id of this component
	// add = true => if it's a new type then add it to the collection
	typenumber =  World::getInstance()->getComponentTypeID(this->type);
}


Component::~Component(void) 
{}
