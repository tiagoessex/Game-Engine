



// Venator headers
#include "DebugShits.h"
#include "Globals.h"
#include "renderengine/StaticText.h"
#include "renderengine/RenderManager.h"
#include "InputManager.h"

// ogre headers
#include <OgreString.h>
#include <OgreConfigFile.h>
#include <OgreResourceGroupManager.h>
#include <OgreTextureManager.h>
#include <OgreMeshManager.h>
#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>

// c++ headers
#include <cassert>

using namespace Venator;
using namespace Venator::Debug;
using namespace Venator::RenderEngine;
using namespace Venator::InputEngine;


//DebugShits *DebugShits::mDebugShits = 0;

DebugShits::DebugShits(void) :
								fps(0),
								mRotationalSpeed(0.15f),
								debug_camera(0),
								initialized(false)
{}

DebugShits::~DebugShits(void)
{}

void DebugShits::destroy(void)
{

		InputManager::getInstance()->removeKeyListener( "DebugShits" );
		InputManager::getInstance()->removeMouseListener( "DebugShits" );		
		//RenderManager::getInstance()->getRoot()->removeFrameListener(this);	
		if (fps)
		{
			delete fps;
			fps = 0;
		}
		debug_camera = 0;
		initialized = false;		

//	RenderManager::getInstance()->getRoot()->removeFrameListener(this);

	//if ( getInstance() ) delete mDebugShits;	
}


bool DebugShits::initialise(Ogre::SceneManager* m)
{
	
	
	manager = m;

//	RenderManager::getInstance()->getRoot()->addFrameListener(mDebugShits);

	InputManager::getInstance()->addKeyListener( this, "DebugShits" );
	InputManager::getInstance()->addMouseListener( this, "DebugShits" );
		
	fps = new RenderEngine::StaticText("","debug",0.03f);	

	return true;
}
void DebugShits::setDebugCamera(Ogre::SceneNode* dbg_camera)
{
	debug_camera = dbg_camera;
}

//bool DebugShits::frameRenderingQueued(const Ogre::FrameEvent& evt)
void DebugShits::update(const Scalar& dt)
{	
	static int counter = 0;
	int a = OIS::KC_W;
	if (debug_camera)
	{
		if(InputManager::getInstance()->getKeyboard()->isKeyDown(OIS::KC_W) && debug_camera)
			debug_camera->translate(0,0,-20*dt, Ogre::Node::TS_LOCAL);
		if(InputManager::getInstance()->getKeyboard()->isKeyDown(OIS::KC_S) && debug_camera)
			debug_camera->translate(0,0,20*dt, Ogre::Node::TS_LOCAL);
		if(InputManager::getInstance()->getKeyboard()->isKeyDown(OIS::KC_A) && debug_camera)
			debug_camera->translate(-20*dt,0,0, Ogre::Node::TS_LOCAL);
		if(InputManager::getInstance()->getKeyboard()->isKeyDown(OIS::KC_D) && debug_camera)
			debug_camera->translate(+20*dt,0,0, Ogre::Node::TS_LOCAL);
	}
	
	counter++;
	if (counter==50)
	{
		counter = 0;
		fps->setCaption("FPS: " + Ogre::StringConverter().toString(RenderManager::getInstance()->getWindow()->getLastFPS()));	// player_shoots_master_node	
	}	

	//return true;

}


bool DebugShits::mouseMoved( const OIS::MouseEvent &arg )
{ 	

	if (arg.state.buttonDown(OIS::MB_Right) && debug_camera)
	{
		manager->getSceneNode("cameraNode")->yaw(Ogre::Degree(-mRotationalSpeed * arg.state.X.rel), Ogre::Node::TS_WORLD);
		manager->getSceneNode("cameraNode")->pitch(Ogre::Degree(-mRotationalSpeed * arg.state.Y.rel), Ogre::Node::TS_LOCAL);
	}


	return true;
}
/*
DebugShits& DebugShits::getSingleton(void)
{  
    assert(mDebugShits);
    return *mDebugShits;
}


DebugShits* DebugShits::getInstance( void )
{
	if( !mDebugShits )
	{
        mDebugShits = new DebugShits();
    }
    return mDebugShits;
}*/