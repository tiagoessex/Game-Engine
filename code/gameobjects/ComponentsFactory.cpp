


#include "ComponentsFactory.h"
#include "../Globals.h"
#include "../utils/VenatorUtils.h"		// only for Number2String

//#include "GameObjectsRegistrations.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


ComponentsFactory *ComponentsFactory::mComponentsFactory = 0;


ComponentsFactory::ComponentsFactory() 
{
	mComponentsFactory = this;
}
	
ComponentsFactory::~ComponentsFactory(void) 
{}


void ComponentsFactory::initialise(void) 
{
	LOGINFO("[ComponentsFactory::initialise] ComponentsFactory initiating ...");

	//registerComponents(this);
	
	LOGINFO("[ComponentsFactory::initialise] ComponentsFactory INITIATED");
}

void ComponentsFactory::destroy(void) 
{

	reset();

	LOGINFO("[ComponentsFactory::destroy] ComponentsFactory DESTROYED");
	delete mComponentsFactory;
}


void ComponentsFactory::reset(void) 
{
	factories.clear();
	componentsIDMap.clear();
}


void ComponentsFactory::registerComponent(const std::string& name, CPOS id, Component::CompBaseFactory* f) 
{
    factories[name] = f;
	componentsIDMap[name] = id;
}

void ComponentsFactory::unregisterComponent(const std::string& name) 
{
    std::map<std::string,Component::CompBaseFactory *>::iterator it = factories.find(name);
    if( it == factories.end() ) {
        return;
	}
    factories.erase(it);

	std::map<std::string, CPOS >::iterator it2 = componentsIDMap.find(name);
	if( it2 == componentsIDMap.end() ) {
        return;
	}
	componentsIDMap.erase(it2);
}


Component* ComponentsFactory::createComponent(const std::string& name) 
{
    std::map<std::string,Component::CompBaseFactory *>::iterator it = factories.find(name);
    if( it == factories.end() ) {
        return 0;
	}
    return factories[name]->createInstance();
}


void ComponentsFactory::destroyComponent(Component* c) 
{
	c->end();
	delete c;
	c = 0;
}

CPOS ComponentsFactory::getComponentTypeID(const std::string& name) 
{
	std::map<std::string, CPOS >::iterator it2 = componentsIDMap.find(name);
	if( it2 != componentsIDMap.end() ) {
		return (*it2).second;
	}
	return 0;
}

ComponentsFactory* ComponentsFactory::getInstance( void ) 
{
    if( !mComponentsFactory ) {
        mComponentsFactory = new ComponentsFactory();
    }
    return mComponentsFactory;
}