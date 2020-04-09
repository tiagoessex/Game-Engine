
/**

	debug shits

	tasks:
		- fps
		- camera control movs

*/

#ifndef __DebugShits_h_
#define __DebugShits_h_


#include "Prerequisites.h"


//#include <OgreFrameListener.h>
#include <OgreNode.h>
#include <OgreSceneManager.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>


namespace Venator {	
	namespace RenderEngine {
		class StaticText;
	}
	namespace Debug	{
		class DebugShits;
	}
}

class Venator::Debug::DebugShits : public OIS::KeyListener, OIS::MouseListener //public Ogre::FrameListener, 
{
	public:	
		DebugShits(void);
		virtual ~DebugShits(void);

		bool initialise(Ogre::SceneManager* manager);
		void destroy(void);		
		void setDebugCamera( Ogre::SceneNode* dbg_camera);
		void update(const Scalar& dt);


//		static DebugShits* getInstance(void);
//		static DebugShits& getSingleton(void);

	private:
	/*	DebugShits(void);
		virtual ~DebugShits(void);
		DebugShits( const DebugShits& ) { }
		DebugShits & operator = ( const DebugShits& );

		static DebugShits *mDebugShits;
		*/
		// loop
		/*virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual bool frameStarted(const Ogre::FrameEvent& evt) { return true; };
		virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; };
		*/
		

		// controls
		virtual bool keyPressed( const OIS::KeyEvent &arg ) { return true; };
		virtual bool keyReleased(const OIS::KeyEvent &keyEventRef) { return true; };

		virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) { return true; }; 
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) { return true; };


		RenderEngine::StaticText* fps;
		Scalar mRotationalSpeed;
		Ogre::SceneNode* debug_camera;
		bool initialized;
		Ogre::SceneManager* manager;
		bool stop;

};		// class


#endif
