
#include "NodeAnimation.h"

#include "../Globals.h"
#include "../utils/VenatorUtils.h"


#include "OgreSceneManager.h"
#include "OgreAnimationState.h"
#include "OgreAnimationTrack.h"
#include "OgreAnimation.h"
#include "OgreKeyFrame.h"


using namespace Venator;
using namespace Venator::RenderEngine;


NodeAnimation::NodeAnimation(void) : 
								mAnimationState(0),
								track(0),
								animation(0),
								key(0),
								manager(0)
{}

NodeAnimation::~NodeAnimation(void)
{

	if (track) { track->removeAllKeyFrames(); }

	if (mAnimationState) {
		manager->destroyAnimationState(animation->getName());
		manager->destroyAnimation(animation->getName());
	}
}

void NodeAnimation::setNode(Ogre::SceneNode* node)
{
	if (track) { track->setAssociatedNode(node); }
}