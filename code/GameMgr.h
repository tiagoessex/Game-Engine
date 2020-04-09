

#ifndef __GameMgr_h_
#define __GameMgr_h_


// c/c++ headers
//#include <vector>
//#include <map>


#include "OgreFrameListener.h"
//#include "OgreNode.h"

#include "OISEvents.h"
#include "OISInputManager.h"
#include "OISKeyboard.h"
#include "OISMouse.h"



namespace Venator {
	class GameMgr;
}


class Venator::GameMgr : public Ogre::FrameListener, OIS::KeyListener, OIS::MouseListener
{
	public:		
		bool initialise(void);
		void destroy(void);
		void reset(void);

		static GameMgr* getInstance(void);
		static GameMgr& getSingleton(void);
	private:
		GameMgr(void);
		virtual ~GameMgr(void);
		GameMgr( const GameMgr& ) { }
		GameMgr & operator = ( const GameMgr& );


		// loop
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt);

		// controls
		virtual bool keyPressed( const OIS::KeyEvent &arg );
		virtual bool keyReleased(const OIS::KeyEvent &keyEventRef);

		virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id); 
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

		static GameMgr *mGameMgr;

};		// class


#endif
