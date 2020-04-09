
#include "SceneNodeAnimManager.h"
#include "NodeAnimation.h"

#include "../Globals.h"
#include "../utils/VenatorUtils.h"

#include "../xml/rapidxml.hpp"
#include "../xml/rapidxml_print.hpp"
#include "../xml/rapidxml_utils.hpp"

#include "OgreSceneManager.h"
#include "OgreAnimationState.h"
#include "OgreAnimationTrack.h"
#include "OgreAnimation.h"
#include "OgreKeyFrame.h"

#include <fstream>


using namespace Venator;
using namespace Venator::RenderEngine;

using namespace rapidxml;



SceneNodeAnimManager *SceneNodeAnimManager::mSceneNodeAnimManager = 0;
 
SceneNodeAnimManager::SceneNodeAnimManager( void )
{}
 
SceneNodeAnimManager::~SceneNodeAnimManager( void ) 
{
	//reset();
}


void SceneNodeAnimManager::initialise(void) 
{
	LOGINFO("[SceneNodeAnimManager::initialise] SceneNodeAnimManager initialized");
}

void SceneNodeAnimManager::destroy(void)
{	
	reset();
	if ( getInstance() ) delete mSceneNodeAnimManager;
}

void SceneNodeAnimManager::reset(void)
{	
	std::vector<NodeAnimation*>::iterator it;
	for (it = collection.begin(); it != collection.end(); it++) {
		delete *it;
		*it = 0;
	}
	collection.clear();
}


bool SceneNodeAnimManager::loadAnimations(const char* filename, Ogre::SceneManager* manager)
{
	rapidxml::xml_document<> doc;
	std::vector<char> buffer;

	std::ifstream in(filename);
	buffer.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>( ));
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

	xml_node<> *start_from = 0;
	start_from = doc.first_node("nodeanimations");
	if (!start_from) {
		LOGERROR("!ERROR -- [NodeAnimations::loadAnimations] -- bad xml file [nodeanimations tag]");
		system("PAUSE");
		return false;
	}
	
	start_from = start_from->first_node("animation");
	if (!start_from) {
		LOGERROR("!ERROR -- [NodeAnimations::loadAnimations] -- bad xml file [animation tag]");
		system("PAUSE");
		return false;
	}
	
	// go through all <animation>
	for (xml_node<> *pElement_entity = start_from; pElement_entity; pElement_entity = pElement_entity->next_sibling()) {
		xml_attribute<> *attr = pElement_entity->first_attribute();
		if (!attr) {
            continue;
		}

		std::string animationName = attr->value();

		xml_node<> *element = pElement_entity->first_node("duration");
		Scalar duration = Utils::String2Number<Scalar>(element->value());

		element = pElement_entity->first_node("type");
		std::string animation_type = element->value();

		element = pElement_entity->first_node("loop");
		std::string loop = element->value();

		element = pElement_entity->first_node("frames");
		Scalar n_frames = Utils::String2Number<Scalar>(element->value());
		Scalar step = duration / n_frames;

		Ogre::AnimationState* animationState;

		Ogre::Animation* animation = manager->createAnimation(animationName,duration);
		animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);	// type
		Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);//,headNode);
	
		

		xml_node<> *pElement_component = pElement_entity->first_node("frame");
		if (!pElement_component) {
           LOGERROR(("!ERROR -- [NodeAnimations::loadAnimations] -- go: [" + std::string(attr->value()) + 
				"] has no specific tag or something is wrong with animations file").c_str());
            continue;
        }

		
		// Keyframes
		Ogre::TransformKeyFrame* framekey;

		int counter = 1;
		for (xml_node<> *key = pElement_component;key; key = key->next_sibling()) {

			framekey = track->createNodeKeyFrame(step * counter);
			counter++;

			xml_node<> *attr_c = key->first_node();
			element = key->first_node("position");
			framekey->setTranslate(Utils::String2Vec3(element->value()));

			element = key->first_node("scale");
			framekey->setScale(Utils::String2Vec3(element->value()));

			element = key->first_node("orientation");
			framekey->setRotation(Utils::String2Quat(element->value()));
		}

		animationState = manager->createAnimationState(animationName);
		animationState->setEnabled(true);
		if (loop == "true") { animationState->setLoop(true); }
			else {animationState->setLoop(false); }
			
		NodeAnimation* temp = new NodeAnimation();
		temp->setNodeAnimation(animationState,track,animation,framekey,manager);
		collection.push_back(temp);
		
	}

	doc.clear();
    buffer.clear();
	return true;
}


NodeAnimation* SceneNodeAnimManager::getNodeAnimation(const std::string& name) 
{
	std::vector<NodeAnimation*>::iterator it;
	for (it = collection.begin(); it != collection.end(); it++) {
		if ((*it)->getAnimation()->getName() == name) {
			return *it;
		}
	}
	return 0;
}

SceneNodeAnimManager* SceneNodeAnimManager::getInstance( void ) 
{
    if( !mSceneNodeAnimManager ) {
        mSceneNodeAnimManager = new SceneNodeAnimManager();
    }
 
    return mSceneNodeAnimManager;
}
