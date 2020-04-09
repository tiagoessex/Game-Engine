


#include "TagsManager.h"
#include "GameObject.h"

#include "../utils/VenatorUtils.h"
#include "../Globals.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


TagsManager *TagsManager::mTagsManager = 0;



TagsManager::TagsManager() {
	LOGTORS("************ TagsManager CTOR ************");
	mTagsManager = this;
}

TagsManager::~TagsManager(void) {
	LOGTORS("************ TagsManager DTOR ************");
}


void TagsManager::initialise(void) {
	LOGINFO("[TagsManager::initialise] TagsManager INITIATED");
}

void TagsManager::destroy(void) {
	
	LOGINFO("[TagsManager::destroy] Destroying TagsManager ...");
	
	reset();

	LOGINFO("[TagsManager::destroy] TagsManager DESTROYED");

	if ( getInstance() ) delete mTagsManager;
}


void TagsManager::receiveEvent(GOSEVENTS ev, void* info) {
	if (ev == DELGO) {
		removeTag(static_cast<GameObject*> (info));		
	}
}



void TagsManager::setTag(GameObject* go, const std::string& tag) {
	TAGSDB::iterator it1 = tags.find(tag);
	if (it1 == tags.end()) {
		GOSVEC newtagcollection;
		newtagcollection.push_back(go);
		tags[tag] = newtagcollection;
		return;
	}
	(*it1).second.push_back(go);
}

void TagsManager::removeTag(GameObject* go, const std::string& tag) {
	TAGSDB::iterator it1 = tags.find(tag);
	GOSVEC::iterator it2;
	if (it1 != tags.end()) {
		for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); it2++) {
            if ((*it2) == go) {
                (*it1).second.erase(it2);
                break;
            }
		}
	}
}

void TagsManager::removeTag(GameObject* go) {
	TAGSDB::iterator it1;
	GOSVEC::iterator it2;
	for (it1 = tags.begin(); it1 != tags.end(); it1++) {
		for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); it2++) {
            if ((*it2) == go) {
                (*it1).second.erase(it2);
                break;
            }
		}
	}
}


bool TagsManager::hasTag(GameObject* go,const std::string& tag) {
	TAGSDB::iterator it1 = tags.find(tag);
	GOSVEC::iterator it2;
	if (it1 != tags.end()) {
		for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); it2++) {
            if ((*it2) == go) {
                return true;
            }
		}
	}
	return false;
}

const std::string& TagsManager::getTag(GameObject* go) {
	TAGSDB::iterator it1;
	GOSVEC::iterator it2;
	for (it1 = tags.begin(); it1 != tags.end(); it1++) {
		for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); it2++) {
            if ((*it2) == go) {
                return (*it1).first;
            }
		}
	}
	return empty;
}


std::vector<GameObject*>& TagsManager::getGameObjectsWithTag(const std::string& tag) {
    TAGSDB::iterator it1 = tags.find(tag);
	if (it1 != tags.end()) {
		return ((*it1).second);
	}
	return emptylist;
}


void TagsManager::reset(void) {
	TAGSDB::iterator it1;
	for (it1 = tags.begin(); it1 != tags.end(); it1++) {
	    (*it1).second.clear();
	}
	tags.clear();
}

void TagsManager::clear(void) {
	reset();
}


TagsManager& TagsManager::getSingleton(void) {
    assert(mTagsManager);
    return *mTagsManager;
}

TagsManager* TagsManager::getInstance( void ) {
    if( !mTagsManager )	{
        mTagsManager = new TagsManager();
    }
    return mTagsManager;
}
