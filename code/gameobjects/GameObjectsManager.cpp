


#include "GameObjectsManager.h"
#include "GameObject.h"
#include "../utils/VenatorUtils.h"
#include "../Globals.h"

#include <iostream>


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


GameObjectsManager *GameObjectsManager::mGameObjectsManager = 0;


GameObjectsManager::GameObjectsManager() {
	LOGTORS("************ GameObjectsManager CTOR ************");	
	mGameObjectsManager = this;
}
	
GameObjectsManager::~GameObjectsManager(void) {
	LOGTORS("************ GameObjectsManager DTOR ************");

	if (gos.size() > 0) {
		destroy();	
	}
}


void GameObjectsManager::initialise(void) {
	gos.clear();
	LOGINFO("[GameObjectsManager::initialise] GameObjectsManager INITIATED");
}

void GameObjectsManager::destroy(void) {
	LOGINFO("[GameObjectsManager::destroy] destroying GameObjectsManager ...");		
	LOGINFO(("[GameObjectsManager::destroy] # eliminating: [" + Utils::Number2String(gos.size()) + "] GOs").c_str());

	GameObject* ent;
	while(!gos.empty()) {		
		ent = gos.back();		
	//	LOGINFO(("[GameObjectsManager::destroy] GameObjectsManager destroyed a GameObject - [" + Utils::Number2String(ent->getID()) + "]").c_str());
		delete ent;
		ent=0;
		gos.pop_back();		
	}	

	gos.clear();

	LOGINFO("[GameObjectsManager::destroy] GameObjectsManager DESTROYED");

	if ( getInstance() ) delete mGameObjectsManager;
}

void GameObjectsManager::addGameObject(GameObject* go) {
	gos.push_back(go);
}

bool GameObjectsManager::removeGameObject(GameObject* go) {
	for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ )	{
		if (*iter == go) {		
			gos.erase(iter);
			return true;
		}
	}
	return false;
}

bool GameObjectsManager::removeGameObject(const LLG& goid) {
	for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ )	{
		if ((*iter)->getID() == goid) {
			gos.erase(iter);
			return true;
		}
	}
	return false;
}


bool GameObjectsManager::deleteGameObject(GameObject* go) {
	for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ ) {
		if (*iter == go) {
			delete go;			
			gos.erase(iter);
			return true;
		}
	}
	return false;
}

bool GameObjectsManager::deleteGameObject(const LLG& goid) {
	for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ )	{
		if ((*iter)->getID() == goid) {
			delete *iter;
			gos.erase(iter);
			return true;
		}
	}
	return false;
}



GameObject* GameObjectsManager::getGameObject(const LLG& goid) {
	for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ )	{
		if ((*iter)->getID() == goid) {
			return *iter;
		}
	}	
	return 0;
}

bool GameObjectsManager::hasGameObject(GameObject* go) {
	for ( std::vector<GameObject*>::iterator iter=gos.begin() ; iter != gos.end(); iter++ )	{
		if ((*iter) == go) {
			return true;
		}
	}	
	return false;
}

void GameObjectsManager::reset(void) {
	LOGINFO(("[GameObjectsManager::reset] # eliminating: [" + Utils::Number2String(gos.size()) + "] GOs").c_str());
	GameObject* ent;
	while(!gos.empty()) {		
		ent = gos.back();		
//		LOGINFO(("[GameObjectsManager::reset] GameObjectsManager destroyed a GameObject - [" + Utils::Number2String(ent->getID()) + "]").c_str());
		delete ent;
		ent=0;
		gos.pop_back();		
	}	
	gos.clear();
}

void GameObjectsManager::clear(void) {
	LOGINFO(("[GameObjectsManager::clear] # eliminating: [" + Utils::Number2String(gos.size()) + "] GOs").c_str());
	reset();
}


GameObjectsManager& GameObjectsManager::getSingleton(void) {  
    assert(mGameObjectsManager);
    return *mGameObjectsManager;
}

GameObjectsManager* GameObjectsManager::getInstance( void ) {
    if( !mGameObjectsManager ) {
        mGameObjectsManager = new GameObjectsManager();
    }
    return mGameObjectsManager;
}