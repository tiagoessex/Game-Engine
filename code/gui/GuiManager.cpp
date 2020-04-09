

#include "GuiManager.h"
#include "../Globals.h"
#include "../InputManager.h"
#include "MainGui.h"
#include "ExitGui.h"

using namespace Venator;
using namespace Venator::GuiSystem;

GuiManager *GuiManager::mGuiManager = 0;

GuiManager::GuiManager() : mRenderer(0)
{}

GuiManager::~GuiManager(void)
{
	if (mRenderer) { destroy(); }
}


void GuiManager::initialise(Ogre::Root* mRoot)
{
	this->mRoot = mRoot;

		// bootstrap
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

	// gui shits
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	// load scheme
	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

	// set defaults
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
		
	// create main window and set it as root
	CEGUI::Window *sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::System::getSingleton().setGUISheet(sheet);	
	
	LOGINFO("GUI system set");	

	// set listeners
//	mRoot->addFrameListener(this);

	// add this obj to input system
	InputEngine::InputManager::getInstance()->addKeyListener( this, "GuiSystem" );
    InputEngine::InputManager::getInstance()->addMouseListener( this, "GuiSystem" );
  //  gameworld->inputmanager->getJoystick( 1 );


	LOGINFO("GuiSystem created");
}

void GuiManager::destroy(void)
{
	// destroy gui collection
	std::map<std::string, BaseGui*>::iterator p;
	for (p = guis.begin(); p != guis.end(); ) {
		if (p->second) {
			delete p->second;
			p->second = 0;
		}
		guis.erase(p++);
	}
	guis.clear();	

	CEGUI::WindowManager::getSingleton().destroyAllWindows();	
	CEGUI::SchemeManager::getSingleton().destroy("TaharezLook.scheme");
	mRenderer->destroySystem();

	//mRoot->removeFrameListener(this);	

	if (mRenderer) { mRenderer = 0; }

	if ( getInstance() ) { delete mGuiManager; }

	LOGINFO("GuiSystem destroyed");
}


///////////////// CREATE A FACTORY ///////////////
BaseGui* GuiManager::createGui(const std::string& name, const std::string& layout, GUIS g)
{
	BaseGui* temp = 0;
	switch (g) {
		case MAIN: 
			{
				temp = new MainGui(name, layout);
			}
			break;
		case EXIT: 
			{
				temp = new ExitGui(name, layout);
			}
			break;
		default: break;
	}

	// failure to create
	if (!temp) { return 0; }

	// gui created => added to collection
	if (temp->loadGui()) {
		guis[name] = temp;
	} else {		// error => delete it and do not added to collection	
		delete temp;
		temp = 0;
	}
	return temp;
}


BaseGui* GuiManager::getGui(const std::string& name) const
{
	//std::map<std::string, BaseGui*>::iterator it;
	int n = guis.count(name);
	if (!n) { return 0; }
	else { return (guis.find(name))->second; }
}



void GuiManager::update(double step)
{
	CEGUI::System::getSingleton().injectTimePulse(step);
}



bool GuiManager::keyPressed( const OIS::KeyEvent &arg )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectKeyDown(arg.key);
	sys.injectChar(arg.text);
	return true;
}

bool GuiManager::keyReleased(const OIS::KeyEvent &arg)
{
	CEGUI::System::getSingleton().injectKeyUp(arg.key);
	return true;
}


bool GuiManager::mouseMoved(const OIS::MouseEvent &arg)
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	////////////////////// *******
	sys.injectMouseMove(static_cast<float>(arg.state.X.rel), static_cast<float>(arg.state.Y.rel));
	////////////////////// *******
	// Scroll wheel.
	if (arg.state.Z.rel) {
		sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);	// 120.0 => magic number
	}

	return true;
}

bool GuiManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonDown(_convertButton(id));
   	return true;
}

bool GuiManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonUp(_convertButton(id));
	return true;
}


// necessary because cegui and ois use different codes for mouse buttons
CEGUI::MouseButton GuiManager::_convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID) {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}


GuiManager* GuiManager::getInstance( void ) 
{
    if( !mGuiManager ) {
        mGuiManager = new GuiManager();
    }
 
    return mGuiManager;
}