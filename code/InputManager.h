
/*

	OIS INPUT MANAGER	v1.3

	tiago c. santos			

	07072012


	notes:	based on Using the Object-oriented Input System Library with OGRE 
			from forum article by brunobg125, jacmoe133512 and Emmeran

	ATT:
		- does not depend on global gameworld

	dependencies:
		- OIS library
		- ogre3d [RenderWindow] - injected


	improvements:
			v1.1 - commented section in initialise
				   if op => always OS mouse pointer and mouse not limited to rendering window
			v1.2 - LOGINFO
			v1.3 - destroy()


	usage:

			in init class:
			
				#inlcude ... 

				InputManager::getInstance()->initialise( mWindow );
				...
				InputManager::getInstance()->destroy();

			in class where need it:		


				#inlcude ... 

				InputManager::getInstance()->addKeyListener( this, "GameManager" );
				InputManager::getInstance()->addMouseListener( this, "GameManager" );
				InputManager::getInstance()->getJoystick( 1 );

				....

				usage 
					if(InputManager::getInstance()->getKeyboard()->isKeyDown(OIS::KC_UP)) ...
					
				....

				


			if class needs : keyPressed, ...
				classs inherits: OIS::KeyListener, OIS::MouseListener

				registers and overlad functions


*/

#ifndef InputManager_H
#define InputManager_H


#include "OISMouse.h"
#include "OISKeyboard.h"
#include "OISJoyStick.h"
#include "OISInputManager.h"
 


namespace Ogre {
	class RenderWindow;
}

namespace Venator {
	namespace InputEngine {
		class InputManager;
	}
}

class Venator::InputEngine::InputManager : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener 
{
	public:
		virtual ~InputManager( void );

		void initialise( Ogre::RenderWindow *renderWindow );
		void destroy(void);
		void capture( void );

		void reset(void);

		void addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName );
		void addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName );
		void addJoystickListener( OIS::JoyStickListener *joystickListener, const std::string& instanceName );

		void removeKeyListener( const std::string& instanceName );
		void removeMouseListener( const std::string& instanceName );
		void removeJoystickListener( const std::string& instanceName );

		void removeKeyListener( OIS::KeyListener *keyListener );
		void removeMouseListener( OIS::MouseListener *mouseListener );
		void removeJoystickListener( OIS::JoyStickListener *joystickListener );

		void removeAllListeners( void );
		void removeAllKeyListeners( void );
		void removeAllMouseListeners( void );
		void removeAllJoystickListeners( void );

		void setWindowExtents( int width, int height );

		OIS::Mouse*    getMouse( void );
		OIS::Keyboard* getKeyboard( void );
		OIS::JoyStick* getJoystick( unsigned int index );

		int getNumOfJoysticks( void );

		static InputManager* getInstance( void );
		static InputManager& getSingleton(void);

	private:
		InputManager( void );
		InputManager( const InputManager& ) { }
		InputManager & operator = ( const InputManager& );

		bool keyPressed( const OIS::KeyEvent &e );
		bool keyReleased( const OIS::KeyEvent &e );

		bool mouseMoved( const OIS::MouseEvent &e );
		bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

		bool povMoved( const OIS::JoyStickEvent &e, int pov );
		bool axisMoved( const OIS::JoyStickEvent &e, int axis );
		bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
		bool buttonPressed( const OIS::JoyStickEvent &e, int button );
		bool buttonReleased( const OIS::JoyStickEvent &e, int button );

		OIS::Mouse        *mMouse;
		OIS::Keyboard     *mKeyboard;
		OIS::InputManager *mInputEngine;

		std::vector<OIS::JoyStick*> mJoysticks;
		std::vector<OIS::JoyStick*>::iterator itJoystick;
		std::vector<OIS::JoyStick*>::iterator itJoystickEnd;

		std::map<std::string, OIS::KeyListener*> mKeyListeners;
		std::map<std::string, OIS::MouseListener*> mMouseListeners;
		std::map<std::string, OIS::JoyStickListener*> mJoystickListeners;

		std::map<std::string, OIS::KeyListener*>::iterator itKeyListener;
		std::map<std::string, OIS::MouseListener*>::iterator itMouseListener;
		std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener;

		std::map<std::string, OIS::KeyListener*>::iterator itKeyListenerEnd;
		std::map<std::string, OIS::MouseListener*>::iterator itMouseListenerEnd;
		std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListenerEnd;

		static InputManager *mInputManager;
};	// class InputManager


#endif