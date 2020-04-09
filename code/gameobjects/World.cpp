


#include "World.h"
#include "GameObjectsManager.h"
#include "GameObject.h"
#include "ComponentsFactory.h"
#include "components/Component.h"
#include "SystemsManager.h"
#include "systems/BaseSystem.h"
#include "TagsManager.h"
#include "GameObjectsFactory.h"
#include "GameObjectsParameters.h"
#include "GameObjectsRegistrations.h"

#include "../utils/VenatorUtils.h"
#include "../GameFiles.h"
#include "../Globals.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


// #################################
// ########### GLOBAL SHITS ########
// #################################

World *World::mWorld = 0;


// #################################
// ########### CTORS/DTORS #########
// #################################

World::World() {
	LOGTORS("************ World CTOR ************");	
}
	
World::~World(void) {
	LOGTORS("************ World DTOR ************");
	mWorld = this;
}

// #################################
// ########## MANAGER SHITS ########
// #################################

void World::initialise(void) {
	LOGINFO("[World::initialise] ########################################");
	LOGINFO("[World::initialise] ########     WORLD INITING    ##########");
	LOGINFO("[World::initialise] ########################################");
	LOGINFO("[World::initialise] initiating GO World ...");

	goManager	= GameObjectsManager::getInstance();
	sysManager	= SystemsManager::getInstance();
	tagsManager = TagsManager::getInstance();
	cFactory	= ComponentsFactory::getInstance();
	goFactory	= GameObjectsFactory::getInstance();
	goparameters= GameObjectsParameters::getInstance();

	LOGINFO("\n--------------- [GameObjectsManager INIT] ---------------");
	goManager->initialise();
	LOGINFO("--------------- [GameObjectsManager END] ---------------");

	LOGINFO("\n--------------- [SystemsManager INIT] ---------------");
	sysManager->initialise();	
	LOGINFO("--------------- [SystemsManager END] ---------------");

	LOGINFO("\n--------------- [TagsManager INIT] ---------------");
	tagsManager->initialise();
	LOGINFO("--------------- [TagsManager END] ---------------");

	LOGINFO("\n--------------- [ComponentsFactory INIT] ---------------");
	cFactory->initialise();	
	LOGINFO("--------------- [ComponentsFactory END] ---------------");

	LOGINFO("\n--------------- [GameObjectsFactory INIT] ---------------");
	goFactory->initialise(DATAFILES.ENTITIES_TEMPLATES);
	LOGINFO("--------------- [GameObjectsFactory END] ---------------");

	LOGINFO("\n--------------- [GameObjectsParameters INIT] ---------------");
	goparameters->initialise(DATAFILES.PARAMETERS_TEMPLATES.c_str());
	LOGINFO("--------------- [GameObjectsParameters END] ---------------");
		
	LOGINFO("\n--------------- [Registriring components and systems INIT] ---------------");
	registerComponents(cFactory);
	registerSystems(this);
	LOGINFO("--------------- [Components and systems registration END] ---------------");

	LOGINFO("[World::initialise] World initiated ....");

	LOGINFO("[World::initialise] ########################################");
	LOGINFO("[World::initialise] ########     WORLD INITED     ##########");
	LOGINFO("[World::initialise] ########################################");
	LOGINFO("##################################################################\n\n");
}

void World::destroy(void) {
	LOGINFO("[World::destroy] ########################################");
	LOGINFO("[World::destroy] ########     WORLD ENDING     ##########");
	LOGINFO("[World::destroy] ########################################");
	LOGINFO("Destroying World ...");
	
	reset();

	goparameters->destroy();
	goFactory->destroy();
	cFactory->destroy();
	goManager->destroy();
	sysManager->destroy();
	tagsManager->destroy();


	LOGINFO("[World::destroy] World DESTROYED");
	LOGINFO("[World::destroy] ########################################");
	LOGINFO("[World::destroy] ########    WORLD DESTROYED   ##########");
	LOGINFO("[World::destroy] ########################################");
	LOGINFO("##################################################################\n\n");

	delete mWorld;
}

void World::reset(void) {
	_clearAll();
	resetBarkerListeners();
	goparameters->reset();
	goFactory->reset();
	tagsManager->reset();
	sysManager->reset();
	cFactory->reset();
	goManager->reset();	
}


void World::clear(void) {
	goManager->clear();
	tagsManager->clear();
	sysManager->clear();

	componentToEliminate.clear();	
	goToEliminate.clear();
	goToRemove.clear();	
}

// #################################
// ########### UPDATE SHITS ########
// #################################

void World::updateWorldStart(const Scalar& dt) {
	deltaStart = dt;
	sysManager->updateStart();
}


void World::updateWorld(const Scalar& dt) {
	delta = dt;
	sysManager->update();
}


void World::updateWorldEnd(const Scalar& dt) {
	deltaEnd = dt;
	sysManager->updateEnd();

	while(!systemToEliminate.empty())  {		
		BaseSystem* temp = systemToEliminate.back();
		sysManager->_deleteSystem(temp);
		removeListener(*temp);
		systemToEliminate.pop_back();		
	}		
	
	for (itergo = goToEliminate.begin(); itergo != goToEliminate.end(); ) {
		GameObject* temp = *itergo;		
		emitEvent(DELGO, (void*) temp);
		goManager->deleteGameObject(temp);			
		temp = 0;
		goToEliminate.erase(itergo++);
	}

	for (itergo = goToRemove.begin(); itergo != goToRemove.end(); ) {
		GameObject* temp = *itergo;		
		emitEvent(REMOVEGO, (void*) temp);	
		temp = 0;
		goToRemove.erase(itergo++);			
	}

	while(!componentToEliminate.empty()) 
	{				
		ComponentOp temp = componentToEliminate.back();
		emitEvent(DELCOMP, (void*) temp.comp);
		temp.go->deleteComponent(temp.comp->getComponentTypeID());			
		componentToEliminate.pop_back();	
	}		
}


// #################################
// ########## GO INTERFACE #########
// #################################

GameObject* World::createGameObject(void) {
	GameObject* temp = new GameObject();
	goCreated.insert(temp);
	return temp;
}

GameObject* World::createGameObject(const PARAMETERSMAP &parameters) {
	GameObject* temp = new GameObject(parameters);
	goCreated.insert(temp);
	return temp;
}

GameObject* World::createGameObjectFromTemplate(const std::string& templatename) {
	GameObject* temp = goFactory->createGameObjectFromTemplate(templatename);
	goCreated.insert(temp);
	return temp;
}

GameObject* World::createGameObjectFromTemplate(const std::string& templatename, const PARAMETERSMAP &parameters) {
	GameObject* temp = goFactory->createGameObjectFromTemplate(templatename, parameters);
	goCreated.insert(temp);
	return temp;
}

void World::addGameObject(GameObject* go) {
	if (goManager->hasGameObject(go)) {
		LOGERROR(("!ERROR -- [World::addGameObject] -- - unable to add GO [" 
			+ Utils::Number2String(go->getID()) + "] - go already in the world").c_str());
		return;
	}

	go->setEnable(true);
	goManager->addGameObject(go);
	emitEvent(ADDGO, (void*) go);

	//***************** EXPERIMENTAL ***************
	// insert tag if any
	PARAMETERSMAP::iterator it = go->parameters.find("tag");
	if (it != go->parameters.end()) {
		setTag(go, (*it).second);
	}
	//***************** EXPERIMENTAL ***************

	LOGINFO(("[World::addGameObject] gameobject [" + Utils::Number2String(go->getID()) + 
		"] added to the world").c_str());

	// now remove it's ref from created go, to avoid Scalar deletion
	goCreated.erase (goCreated.find(go));

}


void World::deleteGameObject(GameObject* go) {
	goToEliminate.insert(go);
}

void World::removeGameObject(GameObject* go) {
	goToRemove.insert(go);
}



GameObject* World::getGameObject(const LLG& id) {
	return goManager->getGameObject(id);
}

void World::reInsertGameObject(GameObject* go) {
	emitEvent(REINSERTEDGO, (void*) go);

	LOGINFO(("[World::addGameObject] gameobject [" + Utils::Number2String(go->getID()) + 
		"] reinserted to the world").c_str());
}

PARAMETERSMAP World::getGOParameters(const std::string& name) {
	return goparameters->getParameters(name);
}


// #################################
// ##### COMPONENTS INTERFACE ######
// #################################

CPOS World::getComponentTypeID(const std::string& component) {
	return cFactory->getComponentTypeID(component);
}


Component* World::createComponent(const std::string& name) {
	return cFactory->createComponent(name);
}



void World::addComponent(GameObject* go, Component* c) {

	if (!c) {
		return;
	}

	ComponentOp temp;
	temp.go = go;
	temp.comp = c;
	temp.comp->setOwner(temp.go);
	if (!temp.go->addComponent(temp.comp)) {	// alreadyt exists
		cFactory->destroyComponent(temp.comp);
		return;
	}

	emitEvent(ADDCOMP, (void*) temp.comp);
}

void World::removeComponent(GameObject* go, Component* c) {
	if (!go->hasComponent(c->getComponentTypeID())) {
		LOGERROR(("!ERROR -- [World::removeComponent] -- - unable to remove component [" 
				+ c->getType() + "] from go [" + Utils::Number2String(go->getID()) + 
					"] - component do not exist").c_str());
		cFactory->destroyComponent(c);
		return;
	}

	ComponentOp temp;
	temp.go = go;
	temp.comp = c;
	componentToEliminate.push_back(temp);
	
}


void World::removeComponent(GameObject* go, const CPOS& id) {	
	if (!go->hasComponent(id)) {
		LOGERROR(("!ERROR -- [World::removeComponent] -- - unable to remove component [" 
					+ Utils::Number2String(id) + "] from go [" + Utils::Number2String(go->getID()) + 
					"] - component do not exist").c_str());
		return;
	}

	ComponentOp temp;
	temp.go = go;	
	temp.comp = go->getComponent(id);
	componentToEliminate.push_back(temp);	
}


void World::removeComponent(GameObject* go, const std::string& component_name) {

	if (!go->hasComponent(component_name)) {
		LOGERROR(("!ERROR -- [World::removeComponent] -- - unable to remove component [" 
					+ component_name + "] from go [" + Utils::Number2String(go->getID()) + 
					"] - component do not exist").c_str());
		return;
	}

	ComponentOp temp;
	temp.go = go;	
	temp.comp = go->getComponent(getComponentTypeID(component_name));
	componentToEliminate.push_back(temp);	
}

// #################################
// ######## SYSTEMS INTERFACE ######
// #################################

void  World::addSystem(BaseSystem* sys) {

	if (!sysManager->_hasSystem(sys->getName())) {
		sysManager->_addSystem(sys, goManager->getEntities());
		addListener(*sys);
	} else {
		LOGERROR(("!ERROR -- [World::addSystem] -- - unable to add system [" 
				+ sys->getName() + "] - system already exists").c_str());
		delete sys;
	}
}

void  World::removeSystem(BaseSystem* sys) {
	systemToEliminate.push_back(sys);
}

void World::removeSystem(const std::string& sysName) {

	if (sysManager->_hasSystem(sysName)) {
		systemToEliminate.push_back(sysManager->_getSystem(sysName));
	} else {
		LOGERROR(("!ERROR -- [World::removeSystem] -- - unable to remove system [" 
				+ sysName + "] - system do not exist").c_str());
	}
}

BaseSystem* World::getSystem(const std::string& sysName) {
	return sysManager->_getSystem(sysName);
}

// #################################
// ########## TAGS INTERFACE #######
// #################################

void World::setTag(GameObject* go, const std::string& tag) {
	tagsManager->setTag(go, tag);
}

void World::removeTag(GameObject* go, const std::string& tag) {
	tagsManager->removeTag(go, tag);
}

void World::removeTag(GameObject* go) {
	tagsManager->removeTag(go);
}

bool World::hasTag(GameObject* go,const std::string& tag) {
	return tagsManager->hasTag(go, tag);
}

const std::string& World::getTag(GameObject* go) {
	return tagsManager->getTag(go);
}

std::vector<GameObject*>& World::getGameObjectsWithTag(const std::string& tag) {
	return tagsManager->getGameObjectsWithTag(tag);
}


// #################################
// ##### XXXXXXXXXXXXXXXXXXXX ######
// #################################

void World::_clearAll(void) {	

	// no need to delete components in componentToEliminate since
	// go will automatically delete them all
	// => just clear the vector	
	componentToEliminate.clear();	

	// no need to delete gos in goToEliminate since
	// gomanager will automatically delete them all
	// => just clear the vector
	goToEliminate.clear();

	// no need to delete, since gomanager takes care of that
	goToRemove.clear();	

	// no need to clear indidually since the manager will do that
	// just clear the vector
	systemToEliminate.clear();

	// eleiminate residuals gos that were never added to the world (gomanager)
	for (std::set <GameObject*>::iterator it=goCreated.begin(); it!=goCreated.end(); ++it) {
		delete (*it);
	}
	goCreated.clear();

}

World& World::getSingleton(void) {  
    assert(mWorld);
    return *mWorld;
}


World* World::getInstance( void ) {
    if( !mWorld ) {
        mWorld = new World();
    }
    return mWorld;
}
