


// c/c++ headers
#include <string>

// Venator headers
#include "GameMgr.h"
#include "Globals.h"
#include "GameFiles.h"
#include "InputManager.h"
#include "ResourcesManager.h"
#include "renderengine/RenderManager.h"
#include "renderengine/RenderUtils.h"
#include "states/PlayState.h"
#include "states/IntroState.h"
#include "states/StatesManager.h"
#include "gameobjects/World.h"
#include "events/EventsDispatcher.h"
#include "sound/SoundManager.h"
#include "physics/BulletPhysicsMgr.h"
#include "gui/GuiManager.h"
#include "gui/BaseGui.h"

// ogre headers
#include "OgreSceneManager.h"
#include "OgreRoot.h"


using namespace Venator;
using namespace Venator::GameStates;
using namespace Venator::RenderEngine;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::Events;
using namespace Venator::SoundSystem;
using namespace Venator::PhysicsSystem;
using namespace Venator::GuiSystem;

#define ACTIVATEGUI			0

GameMgr *GameMgr::mGameMgr = 0;

GameMgr::GameMgr(void) 
{}

GameMgr::~GameMgr(void) 
{}

void GameMgr::destroy(void) {
	LOGINFO("[GameMgr::destroy] ########################################");
	LOGINFO("[GameMgr::destroy] ########    START SHUTDOWN    ##########");
	LOGINFO("[GameMgr::destroy] ########################################");

	LOGINFO("[GameMgr::destroy] destoying GameMgr ...");

#if ACTIVATEGUI
	LOGINFO("\n[GameMgr::destroy] -------------- GUI SYSTEM - start -------------");
	GuiManager::getInstance()->destroy();
	LOGINFO("[GameMgr::destroy] -------------- GUI SYSTEM - end -------------\n");
#endif

		
	LOGINFO("\n[GameMgr::destroy] -------------- GO WORLD - start -------------");
	World::getInstance()->destroy();
	LOGINFO("[GameMgr::destroy] -------------- GO WORLD - end -------------\n");
	
	LOGINFO("\n[GameMgr::destroy] -------------- SOUNDS - start -------------");
	SoundManager::getInstance()->destroy();
	LOGINFO("[GameMgr::destroy] -------------- SOUNDS - end -------------\n");

	LOGINFO("\n[GameMgr::destroy] -------------- PHYSICS - start -------------");
	BulletPhysicsMgr::getInstance()->destroy();
	LOGINFO("[GameMgr::destroy] -------------- PHYSICS - end -------------\n");

	
	LOGINFO("\n[GameMgr::destroy] -------------- STATES MANAGER - start -------------");
	StatesManager::getInstance()->destroy();
	LOGINFO("[GameMgr::destroy] -------------- STATES MANAGER - end -------------\n");
	
	LOGINFO("\n[GameMgr::destroy] -------------- RESOURCES MANAGER - start -------------");
	Resources::ResourcesManager::getInstance()->destroy();
	LOGINFO("[GameMgr::destroy] -------------- RESOURCES MANAGER - end -------------\n");


	LOGINFO("\n[GameMgr::destroy] -------------- IO MANAGER - start -------------");
	InputEngine::InputManager::getInstance()->destroy();
	LOGINFO("[GameMgr::destroy] -------------- IO MANAGER - end -------------\n");

	LOGINFO("\n[GameMgr::destroy] -------------- EVENTS - start -------------");
	EventsDispatcher::getInstance()->destroy();
	LOGINFO("[GameMgr::destroy] -------------- EVENTS - end -------------\n");

	LOGINFO("\n[GameMgr::destroy] -------------- RENDER MANAGER - start -------------");
	RenderManager::getInstance()->getRoot()->removeFrameListener(this);	
	RenderManager::getInstance()->destroy();
	LOGINFO("[GameMgr::destroy] -------------- RENDER MANAGER - end -------------\n");	

	LOGINFO("\n[GameMgr::destroy] -------------- DIVERSOS - start -------------");

	LOGINFO("\n[GameMgr::destroy] -------------- DIVERSOS - end -------------");


	LOGINFO("[GameMgr::destroy] GameMgr destroyed");
	LOGINFO("[GameMgr::destroy] ########################################");
	LOGINFO("[GameMgr::destroy] ########   GAME SYSTEM OVER   ##########");
	LOGINFO("[GameMgr::destroy] ########################################");
	LOGINFO("##################################################################\n\n");

	delete mGameMgr;	
}

void GameMgr::reset(void) {
	World::getInstance()->reset();	
	InputEngine::InputManager::getInstance()->reset();
	Resources::ResourcesManager::getInstance()->reset();
	RenderManager::getInstance()->reset();
	StatesManager::getInstance()->reset();
	EventsDispatcher::getInstance()->reset();
	SoundManager::getInstance()->reset();
	BulletPhysicsMgr::getInstance()->reset();
	//GuiManager::getInstance()->reset();
}

bool GameMgr::initialise(void) {
	LOGINFO("[GameMgr::initialise] ########################################");
	LOGINFO("[GameMgr::initialise] ########   GAME SYSTEM INIT   ##########");
	LOGINFO("[GameMgr::initialise] ########################################");
	LOGINFO("[GameMgr::initialise] initing GameMgr ...");	

	LOGINFO("\n[GameMgr::initialise] -------------- RENDER MANAGER - start -------------");
	if (!RenderManager::getInstance()->initialise()) {
		LOGERROR("ERROR! -- [GameMgr::initialise]  -- - unable to init [RenderManager]");
		return false;
	}	
	LOGINFO("[GameMgr::initialise] -------------- RENDER MANAGER - end -------------\n");	


	// add manager to listener
	RenderManager::getInstance()->getRoot()->addFrameListener(this);


	LOGINFO("\n[GameMgr::initialise] -------------- IO MANAGER - start -------------");
	InputEngine::InputManager::getInstance()->initialise(RenderManager::getInstance()->getWindow());		
	InputEngine::InputManager::getInstance()->addKeyListener( this, "GameManager" );
	InputEngine::InputManager::getInstance()->addMouseListener( this, "GameManager" );
	InputEngine::InputManager::getInstance()->getJoystick( 1 );
	LOGINFO("[GameMgr::initialise] -------------- IO MANAGER - end -------------\n");	


	LOGINFO("\n[GameMgr::initialise] -------------- SOUNDS - start -------------");
	SoundManager::getInstance()->initialise();
	LOGINFO("[GameMgr::initialise] -------------- SOUNDS - end -------------\n");
	

	LOGINFO("\n[GameMgr::initialise] -------------- RESOURCES MANAGER - start -------------");
	Resources::ResourcesManager::getInstance()->initialise();		
	LOGINFO("[GameMgr::initialise] -------------- RESOURCES MANAGER - end -------------\n");	
	

	LOGINFO("\n[GameMgr::initialise] -------------- STATES MANAGER - start -------------");
	StatesManager::getInstance()->initialise();
	LOGINFO("\n[GameMgr::initialise] -------------- STATES MANAGER - end -------------");

	LOGINFO("\n[GameMgr::initialise] -------------- EVENTS - start -------------");
	EventsDispatcher::getInstance()->initialise();
	LOGINFO("[GameMgr::initialise] -------------- EVENTS - end -------------\n");
	
	LOGINFO("\n[GameMgr::initialise] -------------- PHYSICS - start -------------");
	BulletPhysicsMgr::getInstance()->initialise(1/180.f, 10, 1/60.f);	
	LOGINFO("[GameMgr::initialise] -------------- PHYSICS - end -------------\n");

#if ACTIVATEGUI
	LOGINFO("\n[GameMgr::initialise] -------------- GUI SYSTEM - start -------------");
	// guisystem needs resources and input init before init 
	GuiManager::getInstance()->initialise(RenderManager::getInstance()->getRoot());
	GuiManager::getInstance()->createGui("main_menu","maingui.layout", GuiSystem::MAIN);
	GuiManager::getInstance()->createGui("exit_menu","exitgui.layout", GuiSystem::EXIT);	
	LOGINFO("[GameMgr::initialise] -------------- GUI SYSTEM - end -------------\n");
#endif

	LOGINFO("\n[GameMgr::initialise] -------------- WORLD GO - start -------------");
	World::getInstance()->initialise();
	LOGINFO("\n[GameMgr::initialise] -------------- WORLD GO - end -------------");
	
	LOGINFO("\n[GameMgr::initialise] -------------- DIVERSOS - start -------------");

	LOGINFO("\n[GameMgr::initialise] -------------- DIVERSOS - end -------------");




	LOGINFO("[GameMgr::initialise] GameMgr initialized");


	
	LOGINFO("[GameMgr::initialise] ########################################");
	LOGINFO("[GameMgr::initialise] ########     START RUNNING    ##########");
	LOGINFO("[GameMgr::initialise] ########################################");
	LOGINFO("##################################################################\n\n");	
	
	// necessary to define these because of the introstate
	Ogre::SceneManager* manager = RenderManager::getInstance()->createSceneManager("primary");	//DefaultSceneManager");	
	RenderManager::getInstance()->createCamera("camera",manager);//, Color(0,0,1));

	// set initial state	
	//StatesManager::getInstance()->changeState(new IntroState());
	StatesManager::getInstance()->changeState(new PlayState());

	// start ticking	
	RenderManager::getInstance()->getRoot()->startRendering();

	LOGINFO("[GameMgr::initialise] ########################################");
	LOGINFO("[GameMgr::initialise] ########      END RUNNING     ##########");
	LOGINFO("[GameMgr::initialise] ########################################");
	LOGINFO("##################################################################\n\n");

	return true;
}


bool GameMgr::frameStarted(const Ogre::FrameEvent& evt) {

	if (shutDown) {
		return false;
	}

	InputEngine::InputManager::getInstance()->capture();
#if ACTIVATEGUI
	GuiManager::getInstance()->update(evt.timeSinceLastFrame);
#endif
	PhysicsSystem::BulletPhysicsMgr::getInstance()->updateStart();

	return StatesManager::getInstance()->getCurrentState()->updateStart(evt.timeSinceLastFrame);

}


bool GameMgr::frameRenderingQueued(const Ogre::FrameEvent& evt) {	
	PhysicsSystem::BulletPhysicsMgr::getInstance()->update(evt.timeSinceLastFrame);
	return StatesManager::getInstance()->getCurrentState()->update(evt.timeSinceLastFrame);
}

bool GameMgr::frameEnded(const Ogre::FrameEvent& evt) {	
	PhysicsSystem::BulletPhysicsMgr::getInstance()->updateEnd();	
	return StatesManager::getInstance()->getCurrentState()->updateEnd(evt.timeSinceLastFrame);
}

bool GameMgr::mouseMoved( const OIS::MouseEvent &arg ) { 	
	return StatesManager::getInstance()->getCurrentState()->mouseMoved(arg);
}
 
bool GameMgr::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return StatesManager::getInstance()->getCurrentState()->mousePressed(arg,id);
}

bool GameMgr::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return StatesManager::getInstance()->getCurrentState()->mouseReleased(arg,id);
}
 
bool GameMgr::keyPressed( const OIS::KeyEvent &arg ) {		
	switch (arg.key) {
		case OIS::KC_ESCAPE:
			shutDown = true;
			break;	
#if ACTIVATEGUI
		case OIS::KC_M:
			GuiManager::getInstance()->getGui("exit_menu")->setVisible(false);
			GuiManager::getInstance()->getGui("main_menu")->setVisible(true);
			break;
		case OIS::KC_N:
			GuiManager::getInstance()->getGui("exit_menu")->setVisible(true);
			GuiManager::getInstance()->getGui("main_menu")->setVisible(false);
			break;
#endif
		default:
			break;
	}

	return StatesManager::getInstance()->getCurrentState()->keyPressed(arg);
}
 

bool GameMgr::keyReleased( const OIS::KeyEvent &arg ) {	
	return StatesManager::getInstance()->getCurrentState()->keyReleased(arg);
}



GameMgr& GameMgr::getSingleton(void) {  
    assert(mGameMgr);
    return *mGameMgr;
}


GameMgr* GameMgr::getInstance( void ) {
	if( !mGameMgr )	{
        mGameMgr = new GameMgr();
    }
    return mGameMgr;
}