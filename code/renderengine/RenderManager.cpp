
/*
#   ifndef OGRE_DEBUG_MODE
#      ifdef _DEBUG
#         define OGRE_DEBUG_MODE 1
#      else
#         define OGRE_DEBUG_MODE 0
#      endif
#   endif
*/

// venator headers
#include "RenderManager.h"
#include "CamerasManager.h"
#include "RenderUtils.h"
#include "SceneNodeAnimManager.h"

#include "../Globals.h"			// log
#include "../GameFiles.h"			// config files



// ogre headers
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreEntity.h"

using namespace Venator;
using namespace Venator::RenderEngine;


RenderManager *RenderManager::mRenderManager = 0;


RenderManager::RenderManager(): 
					mRoot(0),
					mWindow(0),
					camMgr(0),
					nodeAnimMgr(0)

{}
	
RenderManager::~RenderManager(void) 
{
	mWindow->removeAllViewports();
	mWindow->destroy();

	delete mRoot;		
}

void RenderManager::reset(void) 
{
	if (camMgr)		{ camMgr->reset(); };
	if (nodeAnimMgr){ nodeAnimMgr->reset(); };
}



/*
	set root
	load plugins from file
	set log file
*/
void RenderManager::setRoot(void) 
{
	Ogre::String conf = CONFIGFILES.SETTINGS;
	Ogre::String mPluginsCfg = CONFIGFILES.PLUGINS;
	Ogre::String log = CONFIGFILES.OGRELOG;

	if(OGRE_DEBUG_MODE)	{
		//mPluginsCfg.append("_d");
		mPluginsCfg = CONFIGFILES.PLUGINS_D;
		LOGINFO("[RenderManager::setRoot] ############## DEBUG MODE #############");
	} else {
		LOGINFO("[RenderManager::setRoot] ############## RELEASE MODE #############");
	}

	mRoot = new Ogre::Root(mPluginsCfg, conf, log);
		
	LOGINFO("[RenderManager::setRoot] ROOT SET");
}


/*
	RENDER SYSTEM - configuration dialog + initialise the system
 */
bool RenderManager::setRenderSystem(void)
{

	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog())) {
		LOGERROR("!ERROR -- [RenderManager::setRenderSystem] -- - unable to set the configuration for the render system");
		return false;
	}

	
//	if(!mRoot->showConfigDialog())
//		return false;
	
	LOGINFO("[RenderManager::setRenderSystem] RENDER SYSTEM SET");

	return true;
}

bool RenderManager::createRenderWindow(void) 
{
	mWindow = mRoot->initialise(true, "Venator Studios");
	if (mWindow) {
		LOGINFO("[RenderManager::createRenderWindow] RENDER WINDOW CREATED");
		return true;
	}
	LOGERROR("!ERROR -- [RenderManager::createRenderWindow] -- - unable to create a window");
	return false;
}


bool RenderManager::initialise(void)
{	
	LOGINFO("[RenderManager::initialise] ----------------------------");
	if (mRenderManager)	{		
		setRoot();	
		if (!setRenderSystem()) {
			return false;
		}

		if (!createRenderWindow()) {
			return false;
		}

		camMgr = CamerasManager::getInstance();
		camMgr->initialise();

		nodeAnimMgr = SceneNodeAnimManager::getInstance();
		nodeAnimMgr->initialise();

		LOGINFO("[RenderManager::initialise] RenderManager SETUP DONE");
		LOGINFO("[RenderManager::initialise] ----------------------------");
		return true;
	}

	LOGERROR("!ERROR -- [RenderManager::initialise] -- - unable to setup RenderManager");

	return false;
}

void  RenderManager::destroy(void)
{

	camMgr->destroy();
	camMgr = 0;

	nodeAnimMgr->destroy();
	nodeAnimMgr = 0;

	delete mRenderManager;
}

RenderManager& RenderManager::getSingleton(void) 
{  
    assert(mRenderManager);
    return *mRenderManager;
}


RenderManager* RenderManager::getInstance( void ) 
{
    if( !mRenderManager ) {
        mRenderManager = new RenderManager();
    }
    return mRenderManager;
}



// **********************
// *** SCENES MANAGER ***
// **********************

Ogre::SceneManager* RenderManager::createSceneManager(const std::string& name, Ogre::SceneType type)
{
	return mRoot->createSceneManager(type, name);
}

void RenderManager::removeSceneManager(const std::string& name) 
{
	mRoot->getSceneManager(name)->clearScene();
	mRoot->destroySceneManager(mRoot->getSceneManager(name));	
}

Ogre::SceneManager* RenderManager::getSceneManager(const std::string& name)
{
	return mRoot->getSceneManager(name);
}


// **********************
// *** CAMERAS MANAGER **
// **********************

Ogre::Camera* RenderManager::createCamera(const std::string& name, 
									Ogre::SceneManager* manager,
									const Ogre::ColourValue& bkcolor,
									Ogre::Real clipnear,
									Ogre::Real clipfa,
									int zorder) 
{
	return camMgr->_createCamera(name, manager, bkcolor, clipnear, clipfa, zorder);
}

void RenderManager::removeCamera(const std::string& name) 
{
	camMgr->_removeCamera(name);
}

Ogre::Camera* RenderManager::getCamera(const std::string& name) 
{
	return camMgr->_getCamera(name);
}

bool RenderManager::hasCamera(const std::string& name) 
{
	return camMgr->_hasCamera(name);
}


// **********************
// *** OGRE INTERFACE ***
// **********************
/*
Ogre::SceneNode* RenderManager::createNode(Ogre::SceneManager* manager, Ogre::SceneNode* parent) 
{
	if (parent) {
		return parent->createChildSceneNode();
	} else {
		return manager->createSceneNode();
	}
}

Ogre::SceneNode* createNode(Ogre::SceneManager* manager, const std::string& name,  Ogre::SceneNode* parent = 0) 
{
	if (parent) {
		return parent->createChildSceneNode(name);
	} else {
		return manager->createSceneNode(name);
	}
}

void RenderManager::destroyNode(Ogre::SceneNode* node)
{
	RenderEngine::clearSceneNode(node);
}
*/
/*
Ogre::Entity* RenderManager::createEntity(const std::string& filemesh, Ogre::SceneManager* manager, Ogre::SceneNode* node) 
{
	Ogre::Entity* ent = manager->createEntity(filemesh);
	if (node) {
		node->attachObject(ent);
	}
	return ent;
}
*/

/*
void RenderManager::destroyEntity(Ogre::Entity* entity)
{
	if (entity->isAttached()) {
		entity->getParentSceneNode()->detachObject(entity);
	}
	entity->_getManager()->destroyEntity(entity);
}
*/



// ****************************
// *** SCENE NODE ANIMATION ***
// ****************************
bool RenderManager::loadAnimations(const char* filename, Ogre::SceneManager* manager)
{
	return nodeAnimMgr->loadAnimations(filename, manager);
}

bool RenderManager::loadAnimations(const char* filename, const std::string& managername)
{
	Ogre::SceneManager* manager = mRoot->getSceneManager(managername);
	if (manager) {
		return nodeAnimMgr->loadAnimations(filename, manager);
	} else {
		LOGERROR("!ERROR -- [RenderManager::loadAnimations] -- - unable to load animation file");	
	}	
	return false;
}

NodeAnimation* RenderManager::getNodeAnimation(const std::string& name)
{
	return nodeAnimMgr->getNodeAnimation(name);
}