


#include "GameObjectsFactory.h"
#include "GameObject.h"
#include "ComponentsFactory.h"
#include "../utils/VenatorUtils.h"
#include "../Globals.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace rapidxml;

GameObjectsFactory *GameObjectsFactory::mGameObjectsFactory = 0;


GameObjectsFactory::GameObjectsFactory() {
	LOGTORS("************ GameObjectsFactory CTOR ************");	
	mGameObjectsFactory = this;
}
	
GameObjectsFactory::~GameObjectsFactory(void) {
	LOGTORS("************ GameObjectsFactory DTOR ************");
}


void GameObjectsFactory::initialise(const std::string& templatefile) {
	std::ifstream in(templatefile);
	buffer.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>( ));
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

	xml_node<> *start_from = 0;
	start_from = doc.first_node("gos");
	if (!start_from) {
		LOGERROR("!ERROR -- [GameObjectsFactory::initialise] -- bad xml file [gos tag]");
		return;
	}
	start_from = start_from->first_node("go");
	if (!start_from) {
		LOGERROR("!ERROR -- [GameObjectsFactory::initialise] -- bad xml file [go tag]");
		return;
	}
	

	for (xml_node<> *pElement_entity = start_from; pElement_entity; pElement_entity = pElement_entity->next_sibling()) {
		xml_attribute<> *attr = pElement_entity->first_attribute();
		if (!attr) {
            continue;
		}

		std::vector<std::string> temp;

		xml_node<> *pElement_component = pElement_entity->first_node("components");
		if (!pElement_component) {
           LOGERROR(("!ERROR -- [GameObjectsFactory::initialise] -- go: [" + std::string(attr->value()) + 
				"] has no specific components or something is wrong with template file").c_str());
            continue;
        }


        pElement_component = pElement_component->first_node("component");
        if (!pElement_component) {
            continue;
		}

        for (;pElement_component; pElement_component = pElement_component->next_sibling()) {
            xml_attribute<> *attr_c = pElement_component->first_attribute();
			temp.push_back( attr_c->value() );
	    }

		templates[attr->value()] = temp;
		temp.clear();
	}

	doc.clear();
    buffer.clear();

	LOGINFO("[GameObjectsFactory::initialise] GameObjectsFactory INITIATED");
	LOGINFO("[GameObjectsFactory::initialise] all valid GO templates have been build");	
	LOGINFO(("[GameObjectsFactory::initialise] number of templates: " +  Utils::Number2String(templates.size())).c_str());
}

void GameObjectsFactory::destroy(void) {
	reset();	
	doc.clear();
    buffer.clear();
	LOGINFO("[GameObjectsFactory::destroy] GameObjectsFactory DESTROYED");
	delete mGameObjectsFactory;
}


void GameObjectsFactory::reset(void) {
	std::map<std::string, std::vector<std::string> >::iterator it;
	for (it = templates.begin(); it != templates.end(); it++) {
		(*it).second.clear();	// clear components plan
	}
	templates.clear();			// clear all templates
}


void GameObjectsFactory::_populate(GameObject* temp, const std::string& templatename) {
	Component* c = 0;

	std::map<std::string, std::vector<std::string> >::iterator it = templates.find(templatename);

	// template does not exist => empty go
	if (it == templates.end()) {
		return;
	}
	for (std::vector<std::string>::iterator iter = (*it).second.begin(); iter != (*it).second.end(); iter++) {
		c = ComponentsFactory::getInstance()->createComponent((*iter));		
		if (c) {
			c->setOwner(temp);
			if (!temp->addComponent(c)) {	// already exists
				c->end();
				delete c;
				c = 0;
				//ComponentsFactory::getInstance()->destroyComponent(c);
			}
		}
	}
}

GameObject* GameObjectsFactory::createGameObjectFromTemplate(const std::string& templatename) {
	GameObject* temp = new GameObject();
	_populate(temp, templatename);
	return temp;
}


GameObject* GameObjectsFactory::createGameObjectFromTemplate(const std::string& templatename, const PARAMETERSMAP &params) {
	GameObject* temp = new GameObject(params);
	_populate(temp, templatename);
	return temp;
}

GameObjectsFactory& GameObjectsFactory::getSingleton(void) {  
    assert(mGameObjectsFactory);
    return *mGameObjectsFactory;
}

GameObjectsFactory* GameObjectsFactory::getInstance( void ) {
    if( !mGameObjectsFactory ) {
        mGameObjectsFactory = new GameObjectsFactory();
    }
    return mGameObjectsFactory;
}

