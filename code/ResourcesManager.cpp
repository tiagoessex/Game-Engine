



// Venator headers
#include "ResourcesManager.h"
//#include "GameWorld.h"
//#include "Globals.h"
#include "GameFiles.h"
#include "sound/SoundManager.h"
#include "Globals.h"

// ogre headers
#include "OgreString.h"
#include "OgreConfigFile.h"
#include "OgreResourceGroupManager.h"
#include "OgreTextureManager.h"
#include "OgreMeshManager.h"
#include "OgreMaterialManager.h"
#include "OgreSceneManager.h"
#include "OgreRoot.h"


// c++ headers
#include <cassert>

using namespace Venator;
using namespace Venator::Resources;
using namespace Venator::SoundSystem;

ResourcesManager *ResourcesManager::mResourcesManager = 0;

ResourcesManager::ResourcesManager(void)
{}

ResourcesManager::~ResourcesManager(void) 
{}

void ResourcesManager::reset(void) 
{
	Ogre::MeshManager::getSingleton().unloadUnreferencedResources();
	Ogre::MaterialManager::getSingleton().unloadUnreferencedResources();
	Ogre::TextureManager::getSingleton().unloadUnreferencedResources();

	
	/*Ogre::MeshManager::getSingleton().unloadAll();
	Ogre::MaterialManager::getSingleton().unloadAll();
	Ogre::TextureManager::getSingleton().unloadAll();*/
//	Ogre::GpuProgramManager::getSingleton().unloadUnreferencedResources();
	
	Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("General");
	Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("Popular");

	Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("Imagesets");
	Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("Fonts");
	Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("Schemes");
	Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("LookNFeel");
	Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("Layouts");
	
	//?????????????????????	
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("General");
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("Popular");
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("Imagesets");
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("Fonts");
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("Schemes");
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("LookNFeel");
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("Layouts");

	Ogre::MeshManager::getSingleton().removeAll();
	Ogre::MaterialManager::getSingleton().removeAll();
	Ogre::TextureManager::getSingleton().removeAll();
	//?????????????????????	
}

void ResourcesManager::destroy(void)
{

	LOGINFO(("[ResourcesManager::destroy] mem [MeshManager] > " + Ogre::StringConverter().toString(Ogre::MeshManager::getSingleton().getMemoryUsage())).c_str());
	LOGINFO(("[ResourcesManager::destroy] mem [TextureManager] > " + Ogre::StringConverter().toString(Ogre::TextureManager::getSingleton().getMemoryUsage())).c_str());
	LOGINFO(("[ResourcesManager::destroy] mem [MaterialManager] > " + Ogre::StringConverter().toString(Ogre::MaterialManager::getSingleton().getMemoryUsage())).c_str());	
	Ogre::MeshManager * om = Ogre::MeshManager::getSingletonPtr();
	int i = 0;
	Ogre::ResourceManager::ResourceMapIterator mit = om->getResourceIterator();
	while(mit.hasMoreElements()) {
		mit.getNext();
		i++;
	}
	LOGINFO(("[ResourcesManager::destroy] number of remaining meshes in MeshManager > " + Ogre::StringConverter().toString(i)).c_str());


	reset();


	LOGINFO("[ResourcesManager::destroy] resources destroyed");
	LOGINFO(("[ResourcesManager::destroy] mem [MeshManager] > " + Ogre::StringConverter().toString(Ogre::MeshManager::getSingleton().getMemoryUsage())).c_str());
	LOGINFO(("[ResourcesManager::destroy] mem [TextureManager] > " + Ogre::StringConverter().toString(Ogre::TextureManager::getSingleton().getMemoryUsage())).c_str());
	LOGINFO(("[ResourcesManager::destroy] mem [MaterialManager] > " + Ogre::StringConverter().toString(Ogre::MaterialManager::getSingleton().getMemoryUsage())).c_str());	
	i = 0;
	Ogre::ResourceManager::ResourceMapIterator mit2 = om->getResourceIterator();
	while(mit2.hasMoreElements()) {
		mit2.getNext();
		i++;
	}
	LOGINFO(("[ResourcesManager::destroy] number of remaining meshes in MeshManager > " + Ogre::StringConverter().toString(i)).c_str());

	delete mResourcesManager;	
}


bool ResourcesManager::initialise(void) 
{
	LOGINFO("[ResourcesManager::initialise] initiating ResourcesManager...");	

	Ogre::String mResourcesCfg = CONFIGFILES.RESOURCES;	// debug and release
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements()) {
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	// set and init resources
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);	
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	_loadSounds();

	LOGINFO("[ResourcesManager::initialise] ResourcesManager initiated");	

	return true;
}

void ResourcesManager::_loadSounds() 
{
	SoundManager::getInstance()->loadSound("../resources/sounds/musik.wav");
	SoundManager::getInstance()->loadSound("../resources/sounds/bells.wav");
	SoundManager::getInstance()->loadSound("../resources/sounds/bye.wav");
	SoundManager::getInstance()->loadSound("../resources/sounds/explosion.wav");
	SoundManager::getInstance()->loadSound("../resources/sounds/final.wav");
	SoundManager::getInstance()->loadSound("../resources/sounds/musik2.mp3");
	SoundManager::getInstance()->loadSound("../resources/sounds/nextwave.wav");
	SoundManager::getInstance()->loadSound("../resources/sounds/shoot.wav");
	SoundManager::getInstance()->loadSound("../resources/sounds/welcome.wav");
}

ResourcesManager& ResourcesManager::getSingleton(void)
{  
    assert(mResourcesManager);
    return *mResourcesManager;
}


ResourcesManager* ResourcesManager::getInstance( void ) 
{
	if( !mResourcesManager ) {
        mResourcesManager = new ResourcesManager();
    }
    return mResourcesManager;
}