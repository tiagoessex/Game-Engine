

/**
		general pause state

*/


#ifndef __PauseState_h_
#define __PauseState_h_

// Venator headers
#include "GameState.h"


namespace Venator {
	namespace GameStates {
		class PauseState;
	}
}

class Venator::GameStates::PauseState : public GameState {
	public:
		PauseState(void);
		virtual ~PauseState(void);

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

};	// class PauseState

#endif

