


#include "GameObjectsParameters.h"

#include <fstream>
#include "../Globals.h"
#include "../utils/VenatorUtils.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;

using namespace rapidxml;


GameObjectsParameters *GameObjectsParameters::mGameObjectsParameters = 0;


GameObjectsParameters::GameObjectsParameters() {
	LOGTORS("************ GameObjectsParameters CTOR ************");
	mGameObjectsParameters = this;
}

GameObjectsParameters::~GameObjectsParameters(void) {
	LOGTORS("************ GameObjectsParameters DTOR ************");
}


void GameObjectsParameters::initialise(const char* templatefile) {
	std::ifstream in(templatefile);
	buffer.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>( ));
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

/*	xml_node<> *start_from = 0;
	start_from = doc.first_node("level");
	if (!start_from) {
		LOGERROR("!ERROR -- [GameObjectsParameters::initialise] -- bad xml file [gos tag]");
		return;
	}*/
	xml_node<> *start_from = 0;
	start_from = doc.first_node("gos");
	//start_from = start_from->first_node("gos");
	if (!start_from) {
		LOGERROR("!ERROR -- [GameObjectsParameters::initialise] -- bad xml file [gos tag]");

		return;
	}

	start_from = start_from->first_node("go");
	if (!start_from) {
		LOGERROR("!ERROR -- [GameObjectsParameters::initialise] -- bad xml file [go tag]");
		return;
	}

	for (xml_node<> *pElement_entity = start_from; pElement_entity; pElement_entity = pElement_entity->next_sibling()) {
		xml_attribute<> *attr = pElement_entity->first_attribute();
		if (!attr) {
            continue;
		}

		PARAMETERSMAP temp;

        xml_node<> *pElement_component = pElement_entity->first_node();

        for (;pElement_component; pElement_component = pElement_component->next_sibling()) {
            xml_attribute<> *attr_c = pElement_component->first_attribute();
			temp[pElement_component->name()] = pElement_component->value();
	    }

		templates[pElement_entity->first_attribute()->value()] = temp;
		temp.clear();
	}

	doc.clear();
    buffer.clear();

	LOGINFO("[GameObjectsParameters::initialise] GameObjectsParameters INITIATED");
	LOGINFO("[GameObjectsParameters::initialise] all valid GO parameters have been build");
	LOGINFO(("[GameObjectsParameters::initialise] number of templates: " +  Utils::Number2String(templates.size())).c_str());
	
}


PARAMETERSMAP GameObjectsParameters::getParameters(const std::string& name) {
    std::map<std::string, PARAMETERSMAP >::iterator it1;
	for (it1 = templates.begin(); it1 != templates.end(); it1++) {
	    if ((*it1).first == name) {
           // return &(*it1).second;
			 return (*it1).second;
	    }
	}
	return empty;
}

void GameObjectsParameters::destroy(void) {
	reset();
	doc.clear();
    buffer.clear();
	LOGINFO("[GameObjectsParameters::destroy] GameObjectsParameters DESTROYED");
	delete mGameObjectsParameters;
}


void GameObjectsParameters::reset(void) {
   std::map<std::string, PARAMETERSMAP >::iterator it1;
   PARAMETERSMAP::iterator it2;
	for (it1 = templates.begin(); it1 != templates.end(); it1++) {
	    (*it1).second.clear();
	}
	templates.clear();
}


GameObjectsParameters& GameObjectsParameters::getSingleton(void) {
    assert(mGameObjectsParameters);
    return *mGameObjectsParameters;
}

GameObjectsParameters* GameObjectsParameters::getInstance( void ) {
    if( !mGameObjectsParameters ) {
        mGameObjectsParameters = new GameObjectsParameters();
    }
    return mGameObjectsParameters;
}

