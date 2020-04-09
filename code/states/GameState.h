
/**

	abstract state

	note:
		- to implemnt a new state:
			- derive from GameState

*/


#ifndef __GameState_h_
#define __GameState_h_


// c/c++ headers
#include <string>

#include "OISEvents.h"
#include "OISInputManager.h"
#include "OISKeyboard.h"
#include "OISMouse.h"

#include "../Prerequisites.h"

namespace Venator {
	namespace GameStates {
		class GameState;
	}
}
class Venator::GameStates::GameState {
	public:
		GameState(void); 
		virtual ~GameState(void) {};
		virtual void onENTER() = 0;
		virtual void onEXIT() = 0;
		virtual void onPAUSE() = 0;
		virtual void onRESUME() = 0;

		virtual bool updateStart(const Scalar& dt) = 0;
		virtual bool update(const Scalar& dt) = 0;
		virtual bool updateEnd(const Scalar& dt) = 0;

		void changeState(GameState* state);
		void pushState(GameState* state);
		void popState();		
		int getID(void) { return id; };

		virtual bool keyPressed( const OIS::KeyEvent &arg ) = 0;
		virtual bool keyReleased(const OIS::KeyEvent &keyEventRef) = 0;
		virtual bool mouseMoved(const OIS::MouseEvent &arg) = 0;
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0; 
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
			
		int id;

		static int ID;


};	// class GameState



#endif

