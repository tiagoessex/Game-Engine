



#include "PauseState.h"
#include "../Globals.h"


using namespace Venator;
using namespace Venator::GameStates;


PauseState::PauseState(void) {
	LOGTORS("************ PauseState CTOR ************");
} 

PauseState::~PauseState(void) {
	LOGTORS("************ PauseState DTOR ************");
}

void PauseState::onENTER() {
	LOGINFO("[PauseState::onENTER] PauseState onENTER");
	//Ogre::ControllerManager::getSingleton().setTimeFactor(0);		// pause all animated textures (explosions)
}

void PauseState::onEXIT() {
	LOGINFO("[PauseState::onEXIT] PauseState onEXIT");
	//Ogre::ControllerManager::getSingleton().setTimeFactor(1.0f);	// normal speed for all animated textures (explosions)
}

void PauseState::onPAUSE() {
	LOGINFO("[PauseState::onPAUSE] PauseState onPAUSE");
}

void PauseState::onRESUME() {
	LOGINFO("[PauseState::onRESUME] PauseState onRESUME");
}

bool PauseState::keyPressed( const OIS::KeyEvent &arg ) {
	switch (arg.key) {
		case OIS::KC_P:
			popState();
			break;
		default:
			break;
	}
	return true;
}

bool PauseState::keyReleased(const OIS::KeyEvent &keyEventRef) {
	return true;
}

bool PauseState::mouseMoved(const OIS::MouseEvent &arg) {
	return true;
}

bool PauseState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return true;
}

bool PauseState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return true;
}


bool PauseState::updateStart(const Scalar& dt) {
	return true;
}

bool PauseState::update(const Scalar& dt) {
	return true;
}

bool PauseState::updateEnd(const Scalar& dt) {
	return true;
}


