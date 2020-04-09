



#include "IntroState.h"
#include "../Globals.h"
#include "../fader.h"
#include "../renderengine/RenderManager.h"
#include "PlayState.h"

#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayManager.h"




#include "sigc++/sigc++.h"

using namespace Venator;
using namespace Venator::GameStates;
using namespace Venator::RenderEngine;

	

IntroState::IntroState(void):
						fadetime(0),//2
						time(0), //1
						delta(0),
						counter(0),
						indone(false),
						outdone(false),
						nextstate(false)
{
	LOGTORS("************ IntroState CTOR ************");
} 

IntroState::~IntroState(void) {
	LOGTORS("************ IntroState DTOR ************");
}

void IntroState::onENTER() {
	LOGINFO("[IntroState::onENTER] IntroState onENTER");

	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton(); 
	panel = static_cast<Ogre::OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "PanelName"));
	panel->setMetricsMode(Ogre::GMM_RELATIVE);
	panel->setPosition(0, 0);
	panel->setDimensions(1,1);
	panel->setMaterialName("logo_venator");//game_pic
	overlay = overlayManager.create("intro_screens");
	overlay->add2D(panel); 
	overlay->show();

	fader = new Fader("Overlays/FadeInOut","Materials/OverlayMaterial");
	fader->setFadeIn(fadetime);
	fadein = fader->fadeindone.connect( sigc::mem_fun(this, &IntroState::_fadeInDone) ); 
	fadeout = fader->fadeoutdone.connect( sigc::mem_fun(this, &IntroState::_fadeOutDone) ); 
}

void IntroState::onEXIT() {
	LOGINFO("[IntroState::onEXIT] IntroState onEXIT");
	
	//fader->end();
	fader->stop();
	overlay->remove2D(panel);	
	Ogre::OverlayManager::getSingleton().destroyOverlayElement(panel);
 	Ogre::OverlayManager::getSingleton().destroy("intro_screens");

	fadein.disconnect();
	fadeout.disconnect();

	delete fader;
}

void IntroState::onPAUSE() {
	LOGINFO("[IntroState::onPAUSE] IntroState onPAUSE");
}

void IntroState::onRESUME() {
	LOGINFO("[IntroState::onRESUME] IntroState onRESUME");
}

bool IntroState::keyPressed( const OIS::KeyEvent &arg ) {
	switch (arg.key) {
		case OIS::KC_SPACE:
			if (fader->getCurrentOperation() == Fader::FADE_IN) { fader->setFadeIn(0); }
			if (fader->getCurrentOperation() == Fader::FADE_OUT) { fader->setFadeOut(0); }
			break;
		default:
			break;
	}
	return true;
}

bool IntroState::keyReleased(const OIS::KeyEvent &keyEventRef) {
	return true;
}

bool IntroState::mouseMoved(const OIS::MouseEvent &arg) {
	return true;
}

bool IntroState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return true;
}

bool IntroState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return true;
}


bool IntroState::updateStart(const Scalar& dt) {
	return true;
}

bool IntroState::update(const Scalar& dt) 
{
	fader->update(dt);
	if (indone) {
		delta += dt;
		if (delta > time) {
			fader->setFadeOut(fadetime);
			indone = false;
			delta = 0;
		}		
	}

	if (outdone) {
		if (counter == 1) {
			panel->setMaterialName("game_pic");//logo_venator ");//
			fader->setFadeIn(fadetime);
			//delta = 0;
			outdone = false;
		} else {
			nextstate = true;			
		}
	}

	return true;
}

bool IntroState::updateEnd(const Scalar& dt) {
	if (nextstate) { changeState(new PlayState()); }
	return true;
}

void IntroState::_fadeInDone(void) {
	LOGINFO("FADE IN DONE");
	indone = true;
	outdone = false;

}

void IntroState::_fadeOutDone(void) {
	LOGINFO("FADE OUT DONE");
	outdone = true;
	indone = false;
	counter++;
}




