

#include "CamerasManager.h"
#include "../Globals.h"
#include "RenderManager.h"


#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"

using namespace Venator;
using namespace Venator::RenderEngine;

CamerasManager *CamerasManager::mCamerasManager = 0;

CamerasManager::CamerasManager(void)
{}

CamerasManager::~CamerasManager(void) 
{}


void CamerasManager::initialise(void)
{}

void CamerasManager::destroy(void) 
{
	reset();
	delete mCamerasManager;
}

void CamerasManager::reset(void) 
{
	for (CamerasMap::iterator it = cameras.begin(); it != cameras.end(); it++)	{	
		if ((*it).second->isAttached()) {
			(*it).second->getParentSceneNode()->detachObject((*it).second);
			(*it).second->getViewport()->getTarget()->removeViewport((*it).second->getViewport()->getZOrder());
			(*it).second->getSceneManager()->destroyCamera((*it).second);			
		}
	}
	cameras.clear();
}

Ogre::Camera* CamerasManager::_createCamera(const std::string& name, 
											Ogre::SceneManager* manager,
											const Ogre::ColourValue& bkcolor,									
											Ogre::Real clipnear,
											Ogre::Real clipfar,
											int zorder) 
{
	Ogre::Camera* temp = 0;
	try	{
		temp = manager->createCamera(name);	
		temp->setNearClipDistance(clipnear);
		temp->setFarClipDistance(clipfar);
		Ogre::Viewport* vp = RenderManager::getInstance()->getWindow()->addViewport(temp,zorder);
		vp->setBackgroundColour(bkcolor);	
		temp->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		LOGINFO(("[CamerasManager::_createCamera] camera: [" + name + "] created # manager: [" + 
			manager->getName() + "]").c_str());
		cameras[name] = temp;
	} catch(Ogre::Exception& e) {
		LOGERROR(("!ERROR -- [CamerasManager::_createCamera] -- - unable to create camera [" + name + "]: " + e.getFullDescription()).c_str());
	}

	return temp;
}


void CamerasManager::_removeCamera(const std::string& name)
{
	CamerasMap::iterator it=cameras.find(name);
	if (it != cameras.end())	{
		if ((*it).second->isAttached()) {
			(*it).second->getParentSceneNode()->detachObject((*it).second);
			(*it).second->getViewport()->getTarget()->removeViewport((*it).second->getViewport()->getZOrder());
			(*it).second->getSceneManager()->destroyCamera((*it).second);			
		}
		cameras.erase(it);
		LOGINFO(("[CamerasManager::_removeCamera] camera [" + name + "] removed").c_str());
		return;
	}
	
	LOGERROR(("!ERROR - [CamerasManager::_removeCamera] - camera [" + name + "] could not be removed - camera not founded").c_str());
}

bool CamerasManager::_hasCamera(const std::string& name) 
{
	CamerasMap::iterator it=cameras.find(name);
	if (it != cameras.end()) {
		return true;
	}
	return false;
}


Ogre::Camera* CamerasManager::_getCamera(const std::string& name) 
{
	CamerasMap::iterator it=cameras.find(name);
	if (it != cameras.end()) {
		return (*it).second;
	}

	return 0;
}



std::string CamerasManager::_debugPrint(void) 
{
	std::string str;
	for (CamerasMap::iterator it = cameras.begin(); it != cameras.end(); it++) {
		str += "Camera:\t [" + it->first + "]\n";
	}

	return str;
}

CamerasManager& CamerasManager::getSingleton(void) 
{  
    assert(mCamerasManager);
    return *mCamerasManager;
}


CamerasManager* CamerasManager::getInstance(void) 
{
	if( !mCamerasManager )	{
        mCamerasManager= new CamerasManager();
    }
    return mCamerasManager;
}



