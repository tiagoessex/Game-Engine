
/*
	GuiManager class - responsable for setting CEGUI

	dependencies before init:
		- root initiated
		- inputmanager initiated
		- resources initiated

	dependencies:
		- Ogre	[Ogre::Root] - injected


	ATT: 
		- input system must already be active
		- resources must be already loaded
			-*** TO DO: LOAD GUI RESOURCES FROM HERE????? ***
*/



#ifndef _GuiManager_h_
#define _GuiManager_h_

#include <map>

//#include <OgreFrameListener.h>
//#include <OgreRoot.h>

#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>



namespace Venator {
	namespace GuiSystem	{
		class BaseGui;
		class GuiManager;
		enum GUIS { MAIN, EXIT };
	}
}


class Venator::GuiSystem::GuiManager : public OIS::KeyListener, OIS::MouseListener
{
	public:		
		virtual ~GuiManager(void);

		void initialise(Ogre::Root* mRoot);
		void destroy(void);

		/**
			create a new gui
			to do: factory pattern
		*/
		BaseGui* createGui(const std::string& name, const std::string& layout, GUIS g);

		/**
			get a gui from collection by it's unique name
		*/
		BaseGui* getGui(const std::string& name) const;

		void GuiManager::update(double step);	

		static GuiManager* getInstance( void );

	private:
		GuiManager( void );
		GuiManager( const GuiManager& ) { }
		GuiManager & operator = ( const GuiManager& );

		// controls
		bool keyPressed( const OIS::KeyEvent &arg );
		bool keyReleased(const OIS::KeyEvent &keyEventRef);

		bool mouseMoved(const OIS::MouseEvent &arg);
		bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id); 
		bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);	

		CEGUI::MouseButton _convertButton(OIS::MouseButtonID buttonID);

		CEGUI::OgreRenderer* mRenderer;	
		static GuiManager* mGuiManager;
		Ogre::Root* mRoot;

		std::map<std::string, BaseGui*> guis;	// guis collection

};
	

#endif
