

/**
		general pause state

*/


#ifndef __IntroState_h_
#define __IntroState_h_

// Venator headers
#include "GameState.h"

#include "sigc++/sigc++.h"

namespace Ogre {
	class Overlay;
	class OverlayContainer;
}

namespace Venator {
	class Fader;
	namespace GameStates {
		class IntroState;
	}
}

class Venator::GameStates::IntroState : public GameState  {
	public:
		IntroState(void);
		virtual ~IntroState(void);

		void onENTER();
		void onEXIT();
		void onPAUSE();
		void onRESUME();

		bool updateStart(const Scalar& dt);
		bool update(const Scalar& dt);
		bool updateEnd(const Scalar& dt);		

		virtual bool keyPressed( const OIS::KeyEvent &arg );
		virtual bool keyReleased(const OIS::KeyEvent &keyEventRef);
		virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id); 
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	private:
		Fader* fader;
		Ogre::Overlay* overlay;
		Ogre::OverlayContainer* panel;
		sigc::connection fadein;
		sigc::connection fadeout;
		void _fadeInDone(void);		// callback
		void _fadeOutDone(void);	// callback

		double time;		// aux for pic show - max time
		double delta;		// aux for pic show - counter
		bool indone;
		bool outdone;
		int counter;		// aux for pic transition
		double fadetime;	// transition time between in <-> out
		bool nextstate;
};

#endif

