

/*
	setup rendering engine essntials: 
		- set root
		- set render window
		- create/destroy scenes manager
		- ...

*/


#ifndef __RenderManager_h_
#define __RenderManager_h_

#include "OgrePrerequisites.h"
#include "OgreSceneManager.h"
//#include "../Prerequisites.h"

namespace Ogre {
	class Root;
	class RenderWindow;
}

namespace Venator {
	namespace RenderEngine {
		class RenderManager;
		class CamerasManager;
		class SceneNodeAnimManager;
		struct NodeAnimation;
	}
}

class Venator::RenderEngine::RenderManager {
	public:	
		bool initialise(void);			// init all shits
		void destroy(void);
		void reset(void);

		// **********************
		// *** OGRE ROOT      ***
		// **********************
		Ogre::Root* getRoot(void) { return mRoot; };


		// **********************
		// *** RENDERING WINDOW *
		// **********************
		Ogre::RenderWindow* getWindow(void) { return mWindow; };

		// **********************
		// *** SCENES MANAGER ***
		// **********************
		Ogre::SceneManager* createSceneManager(const std::string& name, Ogre::SceneType type = Ogre::ST_GENERIC);
		void removeSceneManager(const std::string& name);
		Ogre::SceneManager* getSceneManager(const std::string& name);

		// **********************
		// *** CAMERAS MANAGER **
		// **********************
		Ogre::Camera* createCamera(const std::string& name, 
									Ogre::SceneManager* manager,
									const Ogre::ColourValue& bkcolor = Ogre::ColourValue(0,0,0),
									Ogre::Real clipnear = 5.0f,
									Ogre::Real clipfar = 1000.0f,
									int zorder = 0);

		void removeCamera(const std::string& name);
		Ogre::Camera* getCamera(const std::string& name);
		bool hasCamera(const std::string& name);

		// **********************
		// *** OGRE INTERFACE ***
		// **********************
		/*Ogre::SceneNode* createNode(Ogre::SceneManager* manager, Ogre::SceneNode* parent = 0);
		Ogre::SceneNode* createNode(Ogre::SceneManager* manager, const std::string& name,  Ogre::SceneNode* parent = 0);
		void destroyNode(Ogre::SceneNode* node);
		*/
		//Ogre::Entity* createEntity(const std::string& filemesh, Ogre::SceneManager* manager, Ogre::SceneNode* node = 0);		
		//void destroyEntity(Ogre::Entity* entity);
		// particles


		// ****************************
		// *** SCENE NODE ANIMATION ***
		// ****************************
		bool loadAnimations(const char* filename, Ogre::SceneManager* manager);
		bool RenderManager::loadAnimations(const char* filename, const std::string& managername);
		NodeAnimation* getNodeAnimation(const std::string& name);
		


		static RenderManager* getInstance( void );
		static RenderManager& getSingleton(void);

	private:
		RenderManager(void);
		~RenderManager(void);
		RenderManager( const RenderManager& ) { }
		RenderManager & operator = ( const RenderManager& );

		Ogre::Root* mRoot;	
		Ogre::RenderWindow* mWindow;

		void setRoot(void);
		bool setRenderSystem(void);
		bool createRenderWindow(void);

		CamerasManager* camMgr;
		SceneNodeAnimManager* nodeAnimMgr;

		static RenderManager *mRenderManager;	

};	// class RenderManager


#endif
