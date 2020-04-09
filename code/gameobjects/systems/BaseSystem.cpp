

#include "BaseSystem.h"
#include "../World.h"
#include "../GameObject.h"
#include "../components/Component.h"
#include "../../utils/VenatorUtils.h"
#include "../../Globals.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



BaseSystem::BaseSystem(const std::string& name, bool all, Scalar deltatime) : 											
											name(name), 
											all(all),
											deltatime(deltatime),
											currentime(0),
											bitfield(MAXCOMPONENTS)
{
	LOGTORS(("************ BaseSystem [" + name + "] CTOR ************").c_str());	
}
	
BaseSystem::~BaseSystem(void) {
	LOGTORS(("************ BaseSystem [" + name + "] DTOR ************").c_str());

	clear();
/*	components.clear();
	gos.clear();
	*/
}

void BaseSystem::handleComponent(const std::string& componentName, bool set) {
	CPOS c_id = World::getInstance()->getComponentTypeID(componentName);	
	if (c_id >= 0) {
		bitfield.set(c_id, set);
		LOGINFO(("[BaseSystem::handleComponent] system: [" + 
					name + "] set to handle component [" + componentName + "]").c_str());
	}
}


void BaseSystem::handleComponent(const CPOS& componentID, bool set) {	
	bitfield.set(componentID, set);
	LOGINFO(("[BaseSystem::handleComponent] system: [" + 
		name + "] set to handle component [" + Utils::Number2String(componentID) + "]").c_str());
}

void BaseSystem::clear(void) {
	/*LOGINFO(("[BaseSystem::clear] system: [" + name + 
		"] # C > " + Utils::Number2String(components.size()) + 
		" GO > " + Utils::Number2String(gos.size())).c_str()); */
	LOGINFO(("[BaseSystem::clear] # system [" + name + "] # clearing: [" + 
		Utils::Number2String(gos.size()) + "] GOs + [" + 
		Utils::Number2String(components.size()) + " components").c_str());
	components.clear();
	gos.clear();
}

void BaseSystem::receiveEvent(GOSEVENTS ev, void* info) {
	switch (ev) {
		case ADDGO:
			{
				_addGameObject(static_cast<GameObject*> (info));
				break;
			}
		case REINSERTEDGO:
			{
				_addGameObject(static_cast<GameObject*> (info));
				break;
			}
		case ADDCOMP:
			{
				_addComponent(static_cast<Component*> (info));
				break;
			}
		case DELGO:
			{
				_removeGameObject(static_cast<GameObject*> (info));
				break;
			}
		case REMOVEGO:
			{
				_removeGameObject(static_cast<GameObject*> (info));
				break;
			}

		case DELCOMP:
			{
				_removeComponent(static_cast<Component*> (info));
				break;
			}
		default: break;
	}
}


void BaseSystem::_addGameObject(GameObject* go) {
	// first check if this go is processed by this system
	// processed => handlecomponent in go::components
	if (!bitfield.is_subset_of(go->getBitField())) {
		return;
	}

	// now that we know that the go is being processed by this system then
	// lets inserted it

	// all ok => then added it depending on the number of components been 
	// processed by the system

	// just 1 comp type => very limited interaction with
	// others components
	if (bitfield.count() == 1 && !all) {		
		//Component* c = go->getComponent(go->getBitField().find_first());
		Component* c = go->getComponent(bitfield.find_first());
		// check if component is already been processed by the system
		for ( std::vector<Component*>::iterator iter=components.begin() ; iter != components.end(); iter++ ) {
			if (c == *iter)
				return;
		}

		components.push_back(c);
	} else {	// more than 1 component type => add entire object
		// check if go already exists	
		for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ ) {
			if (go == *iter)
				return;
		}
		gos.push_back(go);
	}
}

void BaseSystem::_removeGameObject(GameObject* go) {	
	// first check if this go is processed by this system
	// processed => handlecomponent in go::components
	if (!bitfield.is_subset_of(go->getBitField())) {
		return;
	}

	// ok then remove it
	// if only 1 comp is been processed then removed from components
	if (bitfield.count() == 1 && !all) {	
		Component* c = go->getComponent(bitfield.find_first());
		for ( std::vector<Component*>::iterator iter=components.begin() ; iter != components.end(); iter++ ) {
			if (c == *iter)	{
				components.erase(iter);	
				break;
			}
		}
	} else {	// else this system process more than 1 comp of this go	
		for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ )	{
			if (go == *iter) {
				gos.erase(iter);
				break;
			}
		}
	}
}


void BaseSystem::_addComponent(Component* c) {
	// first check if this component can be processed by this system
	if (!bitfield.is_subset_of(c->getOwner()->getBitField())) {
		return;
	}

	// if this system only deals with this type of component
	// then add it to components
	if (bitfield.count() == 1 && !all && bitfield.test(c->getComponentTypeID())) {		
		// check if component is already been processed by the system
		for ( std::vector<Component*>::iterator iter=components.begin() ; iter != components.end(); iter++ ) {
			if (c == *iter)
				return;
		}

		components.push_back(c);
	} else {	// more than 1 component type => check add the entire go if not already
		// check if go already exists	
		for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ ) {
			if (c->getOwner() == *iter)
				return;
		}

		gos.push_back(c->getOwner());
	}
}


void BaseSystem::_removeComponent(Component* c) {
	// first check if this comp is been processed by the system	
	if (!bitfield.test(c->getComponentTypeID())) {
		return;
	}

	// ok then remove it
	if (bitfield.count() == 1 && !all) {	
		for ( std::vector<Component*>::iterator iter=components.begin() ; iter != components.end(); iter++ ) {
			if (c == *iter)	{
				components.erase(iter);	
				return;
			}
		}
	} else {
		for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ )	{
			if (c->getOwner() == *iter)	{
				gos.erase(iter);
				break;
			}
		}
	}	
}




void BaseSystem::_updateSystem(void) {	

	if (deltatime > 0) {
		currentime += World::getInstance()->getDelta();
		if (currentime < deltatime) {
			return;
		}
		currentime = 0;
	}

	if (all) {
		update(gos);
		return;
	} else if (!components.empty()) {
		for (std::vector<Component*>::iterator itr = components.begin(); itr != components.end(); ++itr) {
			update((*itr));
		}
	} else if (!gos.empty()) {
		for (std::vector<GameObject*>::iterator itr = gos.begin(); itr != gos.end(); ++itr)	{
			update((*itr));
		}
	}

}


