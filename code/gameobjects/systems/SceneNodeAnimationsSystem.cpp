

#include "SceneNodeAnimationsSystem.h"
#include "../GameObject.h"
#include "../components/ComponentSceneNodeAnimation.h"
#include "../components/ComponentPosition.h"
//#include "../components/ComponentScale.h"
//#include "../components/ComponentOrientation.h"
#include "../World.h"

//#include "../components//ComponentRender.h"

#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"
#include "../../renderengine/NodeAnimation.h"

#include "OgreAnimationState.h"
#include "OgreAnimationTrack.h"
#include "OgreNode.h"
#include "OgreSceneNode.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



SceneNodeAnimationsSystem::SceneNodeAnimationsSystem(void) : 
			BaseSystem("SceneNodeAnimationsSystem")
{
	LOGTORS("************ SceneNodeAnimationsSystem CTOR ************");	
}
	
SceneNodeAnimationsSystem::~SceneNodeAnimationsSystem(void) {
	LOGTORS("************ SceneNodeAnimationsSystem DTOR ************");
}


void SceneNodeAnimationsSystem::enter() {
	LOGINFO("[SceneNodeAnimationsSystem::enter] SceneNodeAnimationsSystem enter");	
	handleComponent("scenenodeanimation");
}

void SceneNodeAnimationsSystem::update(Component* c) {
	ComponentSceneNodeAnimation* animation = 0;
	ComponentPosition* position = 0;
//	ComponentScale* scale = 0;
	//ComponentOrientation* orientation = 0;
//	ComponentRender* render = 0;
	GameObject* owner = c->getOwner();
	animation = static_cast<ComponentSceneNodeAnimation*> (c);	
	position = static_cast<ComponentPosition*> (owner->getComponent(POSITION));
//	scale = static_cast<ComponentScale*> (owner->getComponent(SCALE));
//	orientation = static_cast<ComponentOrientation*> (owner->getComponent(ORIENTATION));
//	render = static_cast<ComponentRender*> (owner->getComponent(RENDER));

	if (animation->getAnimation()) {
		Ogre::Node* node = animation->getAnimation()->getNodeAnimationTrack()->getAssociatedNode();

		animation->getAnimation()->getAnimationState()->addTime(World::getInstance()->getDelta());	
		if (position) { position->setPosition(node->getPosition()); }
//		if (scale) { scale->setScale(node->getScale()); }
//		if (orientation) { orientation->setOrientation(node->getOrientation()); }
	}

	
}


/*
	void SceneNodeAnimationsSystem::update(all) {
	    SceneManager::AnimationIterator animationIt = mSceneMgr->getAnimationIterator();

      while(animationIt.hasMoreElements()) {
         Animation* animation = animationIt.getNext();
         
         const Animation::NodeTrackList& trackList = animation->_getNodeTrackList();
         
         Animation::NodeTrackList::const_iterator it = trackList.begin();
         Animation::NodeTrackList::const_iterator iend = trackList.end();

         for(; it != iend; ++it) {
            const Ogre::NodeAnimationTrack* track = it->second;
            track->getAssociatedNode()->resetToInitialState();
         }
         
         currentTime += evt.timeSinceLastFrame;
         animation->apply(currentTime);
      }
	 }
	  */


void SceneNodeAnimationsSystem::exit() {
	LOGINFO("[SceneNodeAnimationsSystem::exit] SceneNodeAnimationsSystem exit");
}
