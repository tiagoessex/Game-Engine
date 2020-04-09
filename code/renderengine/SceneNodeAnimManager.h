

/**
	notes:
		- loads all animations from data file
		- each animation is identified by name in the right scenemanager
		- reset => destroys all animations stored in database
		- to get a specific animation call by name through scenemanager
			or by getNodeAnimation(name)
		- only access through rendermanager
		
	ex:
		SceneNodeAnimManager::getInstance()->initialise();
		SceneNodeAnimManager::getInstance()->loadAnimations(DATAFILES.ANIMATIONS.c_str(),manager);
		anim = SceneNodeAnimManager::getInstance()->getNodeAnimation("player");
		anim->setNode(headNode);

		...

		anim->getAnimationState()->addTime(dt);			

*/

#ifndef _SCENENODEANIMMANAGER_H_
#define _SCENENODEANIMMANAGER_H_

#include <vector>
#include "../Prerequisites.h"

namespace Ogre { 
				class SceneManager; 
				class AnimationState;
				class NodeAnimationTrack;
				class Animation;
				class TransformKeyFrame;
				class SceneNode;
};


namespace Venator {
	namespace RenderEngine {
		class SceneNodeAnimManager;
		struct NodeAnimation;
	}
}



class Venator::RenderEngine::SceneNodeAnimManager
{
	protected:
	//public:
		virtual ~SceneNodeAnimManager( void ); 
		void initialise(void);
		void destroy(void);
		void reset(void);

		bool loadAnimations(const char* filename, Ogre::SceneManager* manager);
		NodeAnimation* getNodeAnimation(const std::string& name);

		static SceneNodeAnimManager* getInstance( void );
		friend class RenderManager;
	private:
		SceneNodeAnimManager( void );
		SceneNodeAnimManager( const SceneNodeAnimManager& ) { }
		SceneNodeAnimManager & operator = ( const SceneNodeAnimManager& );  
	
		std::vector<NodeAnimation*> collection;
	
		static SceneNodeAnimManager *mSceneNodeAnimManager;
};




#endif