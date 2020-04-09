
#include "GameObject.h"
#include "components/Component.h"


#include "../Globals.h"
#include "../utils/VenatorUtils.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


LLG GameObject::ID = 0;

GameObject::GameObject(void) :
						id(ID),
						bitfield(MAXCOMPONENTS),
						enabled(true)

{
	LOGTORS(("************ GameObject id: [" + Utils::Number2String(id) + "] CTOR ************").c_str());
	ID++;
}

GameObject::GameObject(const PARAMETERSMAP& parameters) :
						parameters(parameters),
						id(ID),
						bitfield(MAXCOMPONENTS),
						enabled(true)

{
	LOGTORS(("************ GameObject id: [" + Utils::Number2String(id) + "] CTOR ************").c_str());
	ID++;
}

GameObject::~GameObject(void) {
	LOGTORS(("************ GameObject id: [" + Utils::Number2String(id) + "] DTOR ************").c_str());
	

	LOGINFO(("[GameObject::~GameObject] destroying go: [" + Utils::Number2String(id) + "] # number of components [" + Utils::Number2String(components.size()) +
		"]").c_str());
	
	for (std::map<CPOS, Component*>::reverse_iterator itr = components.rbegin(); itr != components.rend(); ++itr) {
		itr->second->end();
		delete itr->second;
		itr->second = 0;
    }
	components.clear();
	parameters.clear();
}


Component* GameObject::getComponent(const CPOS& type) {

	std::map<CPOS, Component*>::iterator itr = components.find(type);
	
	if (itr != components.end()) {		
		return itr->second;		
	}

	LOGERROR(("!ERROR -- [GameObject::getComponent] go [" + Utils::Number2String(id) + "] was unable to get Component: [" + 
					Utils::Number2String(type) + "]").c_str());
	return 0;	
}

Component* GameObject::getComponent(const std::string& name) {
	for (std::map<CPOS, Component*>::iterator itr = components.begin(); itr != components.end(); itr++)	{
		if ( (*itr).second->getType() == name)
			return (*itr).second;
	}

	LOGERROR(("!ERROR -- [GameObject::getComponent] go [" + Utils::Number2String(id) + "] was unable to get Component: [" + 
					name + "]").c_str());
	return 0;	
}




bool GameObject::addComponent(Component* NewComponent) {

	if (hasComponent(NewComponent->getComponentTypeID())) {
		LOGERROR(("!ERROR -- [GameObject::addComponent] go [" + Utils::Number2String(id) + "] was unable to add Component: [" + 
					NewComponent->getType() + "] - component already exists").c_str());
		return false;
	}

	components[NewComponent->getComponentTypeID()] = NewComponent;
	bitfield.set(NewComponent->getComponentTypeID());
	NewComponent->start();
//	LOGINFO(("[GameObject::addComponent] component [" + NewComponent->getType() + 
//		"] # [" + Utils::Number2String(NewComponent->getComponentTypeID()) + "] added to GO [" + Utils::Number2String(id) + "]").c_str());

	return true;
}


bool GameObject::deleteComponent(const CPOS& type) {
	std::map<CPOS, Component*>::iterator itr = components.find(type);
	if (itr != components.end()) {	
		CPOS t = type;	// ****** put inside debug cond ******
		bitfield.set(itr->second->getComponentTypeID(), false);

//		LOGINFO(("[GameObject::deleteComponent] Component: [" + itr->second->getType() + 
//			"] removed from GO [" + Utils::Number2String(id) + "]").c_str());		

		itr->second->end();
		delete itr->second;
		itr->second = 0;

		components.erase(itr);
		
		return true;
	}

	LOGERROR(("!ERROR -- [GameObject::deleteComponent] -- - GO [" + Utils::Number2String(id) + 
		"] was unable to remove Component: [UNKNOWN]").c_str());
	return false;
}


bool GameObject::deleteComponent(Component* c) {

	for (std::map<CPOS, Component*>::iterator itr = components.begin(); itr != components.end(); itr++) {
		if ( (*itr).second == c) {
			bitfield.set(itr->second->getComponentTypeID(), false);

//			LOGINFO(("[GameObject::deleteComponent] Component: [" + itr->second->getType() + 
//				"] removed from GO [" + Utils::Number2String(id) + "]").c_str());		

			itr->second->end();
			delete itr->second;
			components.erase(itr);
			return true;
		}
	}
	
	LOGERROR(("!ERROR -- [GameObject::deleteComponent] -- - GO [" + Utils::Number2String(id) + 
		"] was unable to remove Component: [" + c->getType() + "]").c_str());
	return false;

}


bool GameObject::hasComponent(const CPOS& type) {
	return bitfield.test(type);
}

bool GameObject::hasComponent(const std::string& name) {
	std::map<CPOS, Component*>::iterator itr;
	for (itr = components.begin(); itr != components.end(); ++itr) {
		if (itr->second->getType() == name) {
			return true;
		}
	}
	return false;
}

