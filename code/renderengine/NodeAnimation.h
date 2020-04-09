

// only for storage

#ifndef _NodeAnimation_H_
#define _NodeAnimation_H_


namespace Ogre { 
				class SceneManager; 
				class AnimationState;
				class NodeAnimationTrack;
				class Animation;
				class TransformKeyFrame;
				class SceneNode;
};


namespace Venator {	namespace RenderEngine { struct NodeAnimation; } }


struct Venator::RenderEngine::NodeAnimation
{
		NodeAnimation(void);
		~NodeAnimation(void);					
		void setNodeAnimation(	Ogre::AnimationState* m,
								Ogre::NodeAnimationTrack* t,
								Ogre::Animation* a,
								Ogre::TransformKeyFrame* k,
								Ogre::SceneManager* mgr)
		{
			mAnimationState = m;
			track = t;
			animation = a;
			key = k; 
			manager = mgr;
		}

		void setNode(Ogre::SceneNode* node);

		Ogre::AnimationState* getAnimationState(void) { return mAnimationState; }
		Ogre::NodeAnimationTrack* getNodeAnimationTrack(void) {  return track; }
		Ogre::Animation* getAnimation(void) {  return animation; }
		Ogre::TransformKeyFrame* getTransformKeyFrame(void) { return key; }

	private:
		Ogre::AnimationState* mAnimationState;
		Ogre::NodeAnimationTrack* track;
		Ogre::Animation* animation;
		Ogre::TransformKeyFrame* key;
		Ogre::SceneManager* manager;
};


#endif