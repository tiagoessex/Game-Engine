


#include "SystemsManager.h"
#include "systems/BaseSystem.h"
#include "../Globals.h"
#include "GameObject.h"

#include "../utils/VenatorUtils.h"		// only for Number2String


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


SystemsManager *SystemsManager::mSystemsManager = 0;


SystemsManager::SystemsManager() {
	LOGTORS("************ SystemsManager CTOR ************");	
	mSystemsManager = this;
}
	
SystemsManager::~SystemsManager(void) {
	LOGTORS("************ SystemsManager DTOR ************");

}


void SystemsManager::initialise(void) {
	LOGINFO("[SystemsManager::initialise] SystemsManager INITIATED");
}

void SystemsManager::destroy(void) {
	
	LOGINFO("[SystemsManager::destroy] Destroying SystemsManager ...");
	LOGINFO(("[SystemsManager::destroy] number of registered systems: [" + Utils::Number2String(systems.size()) + "]").c_str());
	
	reset();

	LOGINFO("[SystemsManager::destroy] SystemsManager DESTROYED");
	if ( getInstance() ) { delete mSystemsManager; }
}


void SystemsManager::_addSystem(BaseSystem* system, const std::vector<GameObject*>& gos) {//, bool updatable) {
	LOGINFO(("[SystemsManager::addSystem] System: [" + system->getName() + "] added").c_str());
	systems.push_back(system);
	system->enter();

	for ( std::vector<GameObject*>::const_iterator iter=gos.begin() ; iter != gos.end(); iter++ ) {
		system->_addGameObject(*iter);
	}	
}

bool SystemsManager::_deleteSystem(BaseSystem* system) {
	for ( std::vector<BaseSystem*>::iterator iter=systems.begin() ; iter != systems.end(); iter++ ) {
		if (*iter == system) {		
			system->exit();
//			LOGINFO(("[SystemsManager::deleteSystem] system - [" + system->getName() + "] eliminated").c_str());
			delete system;
			systems.erase(iter);
			return true;
		}
	}
	
	return false;
}

BaseSystem* SystemsManager::_getSystem(const std::string& systemName) {
	for ( std::vector<BaseSystem*>::iterator iter=systems.begin() ; iter != systems.end(); iter++ )	{
		if ((*iter)->getName() == systemName) {		
			return *iter;			
		}
	}

	LOGERROR(("!ERROR -- [SystemsManager::getSystem] -- - unable to find system: [" + 
				systemName + "]").c_str());
	return 0;
}

bool SystemsManager::_hasSystem(const std::string& systemName) {
	for ( std::vector<BaseSystem*>::iterator iter=systems.begin() ; iter != systems.end(); iter++ )	{
		if ((*iter)->getName() == systemName) {		
			return true;
		}
	}

	return false;
}

void SystemsManager::updateStart(void) {
	for (std::vector<BaseSystem*>::iterator itr = systems.begin(); itr != systems.end(); ++itr) {
		(*itr)->updateStart();
	}
}

void SystemsManager::update(void) {
	for (std::vector<BaseSystem*>::iterator itr = systems.begin(); itr != systems.end(); ++itr) {
		(*itr)->_updateSystem();
	}
}

void SystemsManager::updateEnd(void) {
	for (std::vector<BaseSystem*>::iterator itr = systems.begin(); itr != systems.end(); ++itr)	{
		(*itr)->updateEnd();
	}
}



std::string SystemsManager::_debugPrint(void) {
	std::string str;
	for ( std::vector<BaseSystem*>::iterator iter=systems.begin() ; iter != systems.end(); iter++ ) {
		str += "Updatable System:\t type [" + (*iter)->getName() +  "]\n";
	}
	return str;
}

void SystemsManager::reset(void) {
	LOGINFO(("[SystemsManager::reset] # eliminating: [" + Utils::Number2String(systems.size()) + "] systems").c_str());

	BaseSystem* ent;
	while(!systems.empty()) {		
		ent = systems.back();	
		ent->exit();
//		LOGINFO(("[SystemsManager::reset] SystemsManager destroyed the updatable System - [" + ent->getName() + "]").c_str());
		delete ent;
		ent=0;
		systems.pop_back();		
	}	
	systems.clear();
}

void SystemsManager::clear(void) {
	LOGINFO(("[SystemsManager::clear] # clearing: [" + Utils::Number2String(systems.size()) + "] systems").c_str());
	for (std::vector<BaseSystem*>::iterator itr = systems.begin(); itr != systems.end(); ++itr)	{
		(*itr)->clear();
	}
}

SystemsManager& SystemsManager::getSingleton(void) {  
    assert(mSystemsManager);
    return *mSystemsManager;
}

SystemsManager* SystemsManager::getInstance( void ) {
    if( !mSystemsManager ) {
        mSystemsManager = new SystemsManager();
    }
    return mSystemsManager;
}