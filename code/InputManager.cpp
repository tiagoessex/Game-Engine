

#include "InputManager.h"
#include "Globals.h"


#include "OgreRenderWindow.h"


using namespace Venator::InputEngine;


InputManager *InputManager::mInputManager = 0;
 
InputManager::InputManager( void ) :
    mMouse( 0 ),
    mKeyboard( 0 ),
    mInputEngine( 0 ) 
{}
 
InputManager::~InputManager( void ) 
{}

void InputManager::reset(void) 
{
  if( mInputEngine ) {
        if( mMouse ) {
            mInputEngine->destroyInputObject( mMouse );
            mMouse = 0;
        }
 
        if( mKeyboard ) {
            mInputEngine->destroyInputObject( mKeyboard );
            mKeyboard = 0;
        }
 
        if( mJoysticks.size() > 0 ) {
            itJoystick    = mJoysticks.begin();
            itJoystickEnd = mJoysticks.end();
            for(; itJoystick != itJoystickEnd; ++itJoystick ) {
                mInputEngine->destroyInputObject( *itJoystick );
            }
 
            mJoysticks.clear();
        }
 
        // If you use OIS1.0RC1 or above, uncomment this line
        // and comment the line below it
		mInputEngine->destroyInputSystem( mInputEngine );
        //mInputEngine->destroyInputEngine();
        mInputEngine = 0;
 
        // Clear Listeners
        mKeyListeners.clear();
        mMouseListeners.clear();
        mJoystickListeners.clear();
    }
}


void InputManager::destroy(void) 
{
	reset();
	delete mInputManager;
}
 
void InputManager::initialise( Ogre::RenderWindow *renderWindow ) 
{
    if( !mInputEngine ) {
        // Setup basic variables
        OIS::ParamList paramList;    
        size_t windowHnd = 0;
        std::ostringstream windowHndStr;
 
     
	// Get window handle
    //   renderWindow->getCustomAttribute( "WINDOW", &windowHnd );
 
	// Get window handle
#if defined OIS_WIN32_PLATFORM
	renderWindow->getCustomAttribute("WINDOW", &windowHnd);
#elif defined OIS_LINUX_PLATFORM
	renderWindow->getCustomAttribute("GLXWINDOW", &windowHnd);
#endif

        // Fill parameter list
        windowHndStr << (unsigned int) windowHnd;
        paramList.insert( std::make_pair( std::string( "WINDOW" ), windowHndStr.str() ) );
 
// for os mouse => works outside render window:
/*
#if defined OIS_WIN32_PLATFORM
      paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
      paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
      paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
      paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
      paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
      paramList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
      paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
      paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
*/


        // Create InputEngine
        mInputEngine = OIS::InputManager::createInputSystem( paramList );
 
        // If possible create a buffered keyboard
        // (note: if below line doesn't compile, try:  if (mInputEngine->getNumberOfDevices(OIS::OISKeyboard) > 0) {
        //if( mInputEngine->numKeyboards() > 0 ) {
        if (mInputEngine->getNumberOfDevices(OIS::OISKeyboard) > 0)	{
            mKeyboard = static_cast<OIS::Keyboard*>( mInputEngine->createInputObject( OIS::OISKeyboard, true ) );
            mKeyboard->setEventCallback( this );
        }
 
        // If possible create a buffered mouse
        // (note: if below line doesn't compile, try:  if (mInputEngine->getNumberOfDevices(OIS::OISMouse) > 0) {
        //if( mInputEngine->numMice() > 0 ) {
        if (mInputEngine->getNumberOfDevices(OIS::OISMouse) > 0) {
            mMouse = static_cast<OIS::Mouse*>( mInputEngine->createInputObject( OIS::OISMouse, true ) );
            mMouse->setEventCallback( this );
 
            // Get window size
            unsigned int width, height, depth;
            int left, top;
            renderWindow->getMetrics( width, height, depth, left, top );
 
            // Set mouse region
            this->setWindowExtents( width, height );
        }
 
        // If possible create all joysticks in buffered mode
        // (note: if below line doesn't compile, try:  if (mInputEngine->getNumberOfDevices(OIS::OISJoyStick) > 0) {
        //if( mInputEngine->numJoySticks() > 0 ) {
        if (mInputEngine->getNumberOfDevices(OIS::OISJoyStick) > 0) {
            //mJoysticks.resize( mInputEngine->numJoySticks() );
            mJoysticks.resize( mInputEngine->getNumberOfDevices(OIS::OISJoyStick) );
 
            itJoystick    = mJoysticks.begin();
            itJoystickEnd = mJoysticks.end();
            for(; itJoystick != itJoystickEnd; ++itJoystick ) {
                (*itJoystick) = static_cast<OIS::JoyStick*>( mInputEngine->createInputObject( OIS::OISJoyStick, true ) );
                (*itJoystick)->setEventCallback( this );
            }
        }
    }
}
 
void InputManager::capture( void ) {
    // Need to capture / update each device every frame
    if( mMouse ) {
        mMouse->capture();
    }
 
    if( mKeyboard ) {
        mKeyboard->capture();
    }
 
    if( mJoysticks.size() > 0 ) {
        itJoystick    = mJoysticks.begin();
        itJoystickEnd = mJoysticks.end();
        for(; itJoystick != itJoystickEnd; ++itJoystick ) {
            (*itJoystick)->capture();
        }
    }
}
 
void InputManager::addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName ) {
    if( mKeyboard ) {
        // Check for duplicate items
        itKeyListener = mKeyListeners.find( instanceName );
        if( itKeyListener == mKeyListeners.end() ) {
            mKeyListeners[ instanceName ] = keyListener;
			LOGINFO(("[InputManager::addKeyListener] added new key listener [" + instanceName + "]").c_str());
        } else {
            // Duplicate Item
			LOGERROR(("!ERROR - [InputManager::addKeyListener] duplicated key listener [" + instanceName + "]").c_str());
        }
    }	
}
 
void InputManager::addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName ) {
    if( mMouse ) {
        // Check for duplicate items
        itMouseListener = mMouseListeners.find( instanceName );
        if( itMouseListener == mMouseListeners.end() ) {
            mMouseListeners[ instanceName ] = mouseListener;
			LOGINFO(("[InputManager::addMouseListener] added new mouse listener [" + instanceName + "]").c_str());
        } else {
            // Duplicate Item
			LOGERROR(("!ERROR - [InputManager::addMouseListener] duplicated mouse listener [" + instanceName + "]").c_str());
        }
    }	
}
 
void InputManager::addJoystickListener( OIS::JoyStickListener *joystickListener, const std::string& instanceName ) {
    if( mJoysticks.size() > 0 ) {
        // Check for duplicate items
        itJoystickListener = mJoystickListeners.find( instanceName );
        if( itJoystickListener == mJoystickListeners.end() ) {
            mJoystickListeners[ instanceName ] = joystickListener;
			LOGINFO(("[InputManager::addJoystickListener] added new joystick listener [" + instanceName + "]").c_str());
        } else {
            // Duplicate Item
			LOGERROR(("!ERROR - [InputManager::addJoystickListener] duplicated joystick listener [" + instanceName + "]").c_str());
        }
    }
	
}
 
void InputManager::removeKeyListener( const std::string& instanceName ) {
    // Check if item exists
    itKeyListener = mKeyListeners.find( instanceName );
    if( itKeyListener != mKeyListeners.end() ) {
        mKeyListeners.erase( itKeyListener );
		LOGINFO(("[InputManager::removeKeyListener] key listener [" + instanceName + "] removed").c_str());
    } else {
        // Doesn't Exist
		LOGERROR(("!ERROR - [InputManager::removeKeyListener] key listener [" + instanceName + "] do not exist").c_str());
    }
}
 
void InputManager::removeMouseListener( const std::string& instanceName ) {
    // Check if item exists
    itMouseListener = mMouseListeners.find( instanceName );
    if( itMouseListener != mMouseListeners.end() ) {
        mMouseListeners.erase( itMouseListener );
		LOGINFO(("[InputManager::removeMouseListener] mouse listener [" + instanceName + "] removed").c_str());
    } else {
        // Doesn't Exist
		LOGERROR(("!ERROR - [InputManager::removeMouseListener] mouse listener [" + instanceName + "] do not exist").c_str());
    }
}
 
void InputManager::removeJoystickListener( const std::string& instanceName ) {
    // Check if item exists
    itJoystickListener = mJoystickListeners.find( instanceName );
    if( itJoystickListener != mJoystickListeners.end() ) {
        mJoystickListeners.erase( itJoystickListener );
		LOGINFO(("[InputManager::removeJoystickListener] joystick listener [" + instanceName + "] removed").c_str());
    } else {
        // Doesn't Exist
		LOGERROR(("!ERROR - [InputManager::removeJoystickListener] joystick listener [" + instanceName + "] do not exist").c_str());
    }
}
 
void InputManager::removeKeyListener( OIS::KeyListener *keyListener ) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if( itKeyListener->second == keyListener ) {
            mKeyListeners.erase( itKeyListener );
			LOGINFO(("[InputManager::removeKeyListener] key listener [" + itKeyListener->first + "] removed").c_str());
            return;
        }
    }
	LOGERROR(("!ERROR - [InputManager::removeKeyListener] key listener [" + itKeyListener->first + "] do not exist").c_str());
}
 
void InputManager::removeMouseListener( OIS::MouseListener *mouseListener ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if( itMouseListener->second == mouseListener ) {
            mMouseListeners.erase( itMouseListener );
			LOGINFO(("[InputManager::removeMouseListener] mouse listener [" + itKeyListener->first + "] removed").c_str());
            return;
        }
    }
	LOGERROR(("!ERROR - [InputManager::removeMouseListener] mouse listener [" + itKeyListener->first + "] do not exist").c_str());
}
 
void InputManager::removeJoystickListener( OIS::JoyStickListener *joystickListener ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if( itJoystickListener->second == joystickListener ) {
            mJoystickListeners.erase( itJoystickListener );
			LOGINFO(("[InputManager::removeJoystickListener] joystick listener [" + itKeyListener->first + "] removed").c_str());
            return;
        }
    }
	LOGERROR(("!ERROR - [InputManager::removeJoystickListener] joystick listener [" + itKeyListener->first + "] do not exist").c_str());
}
 
void InputManager::removeAllListeners( void ) {
    mKeyListeners.clear();
    mMouseListeners.clear();
    mJoystickListeners.clear();
	LOGINFO("[InputManager::removeAllListeners] all listners removed");
}
 
void InputManager::removeAllKeyListeners( void ) {
    mKeyListeners.clear();
	LOGINFO("[InputManager::removeAllKeyListeners] all key listeners removed");
}
 
void InputManager::removeAllMouseListeners( void ) {
    mMouseListeners.clear();
	LOGINFO("[InputManager::removeAllMouseListeners] all mouse listeners removed");
}
 
void InputManager::removeAllJoystickListeners( void ) {
    mJoystickListeners.clear();
	LOGINFO("[InputManager::removeAllJoystickListeners] all joysticks listeners removed");
}
 
void InputManager::setWindowExtents( int width, int height ) {
    // Set mouse region (if window resizes, we should alter this to reflect as well)
    const OIS::MouseState &mouseState = mMouse->getMouseState();
    mouseState.width  = width;
    mouseState.height = height;
}
 
OIS::Mouse* InputManager::getMouse( void ) {
    return mMouse;
}
 
OIS::Keyboard* InputManager::getKeyboard( void ) {
    return mKeyboard;
}
 
OIS::JoyStick* InputManager::getJoystick( unsigned int index ) {
    // Make sure it's a valid index
    if( index < mJoysticks.size() ) {
        return mJoysticks[ index ];
    }
 
    return 0;
}
 
int InputManager::getNumOfJoysticks( void ) {
    // Cast to keep compiler happy ^^
    return (int) mJoysticks.size();
}
 
bool InputManager::keyPressed( const OIS::KeyEvent &e ) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyPressed( e ))
            break;
    }
 
    return true;
}
 
bool InputManager::keyReleased( const OIS::KeyEvent &e ) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyReleased( e )) {
            break;
		}
    }
 
    return true;
}
 
bool InputManager::mouseMoved( const OIS::MouseEvent &e ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseMoved( e )) {
            break;
		}
    }
 
    return true;
}
 
bool InputManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mousePressed( e, id )) {
            break;
		}
    }
 
    return true;
}
 
bool InputManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if(!itMouseListener->second->mouseReleased( e, id )) {
            break;
		}
    }
 
    return true;
}
 
bool InputManager::povMoved( const OIS::JoyStickEvent &e, int pov ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if(!itJoystickListener->second->povMoved( e, pov )) {
            break;
		}
    }
 
    return true;
}
 
bool InputManager::axisMoved( const OIS::JoyStickEvent &e, int axis ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if(!itJoystickListener->second->axisMoved( e, axis )) {
            break;
		}
    }
 
    return true;
}
 
bool InputManager::sliderMoved( const OIS::JoyStickEvent &e, int sliderID ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if(!itJoystickListener->second->sliderMoved( e, sliderID )) {
			break;
		}
    }
 
    return true;
}
 
bool InputManager::buttonPressed( const OIS::JoyStickEvent &e, int button ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if(!itJoystickListener->second->buttonPressed( e, button )) {
            break;
		}
    }
 
    return true;
}
 
bool InputManager::buttonReleased( const OIS::JoyStickEvent &e, int button ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if(!itJoystickListener->second->buttonReleased( e, button )) {
            break;
		}
    }
 
    return true;
}

InputManager& InputManager::getSingleton(void) {  
    assert(mInputManager);
    return *mInputManager;
}

 
InputManager* InputManager::getInstance( void ) {
    if( !mInputManager ) {
        mInputManager = new InputManager();
    }
 
    return mInputManager;
}