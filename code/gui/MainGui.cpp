
#include "MainGui.h"
#include "../Globals.h"


using namespace Venator;
using namespace Venator::GuiSystem;

MainGui::MainGui(const std::string& name, const std::string& layout) :
				BaseGui(name, layout)
{}



MainGui::~MainGui(void)
{}

bool MainGui::loadGui(void)
{
	if (!BaseGui::loadGui())
	{
		LOGERROR(("!ERROR -- MainGui -- - CAN'T LOAD LAYOUT [" + layout + "] FOR MainGui [" + name + "]").c_str());
		return false;
	}
	RegisterHandlers();
	return true;
}


void MainGui::RegisterHandlers(void)	// param: gamestate* and call this inside gamestate after calling setvisible
{
	if (!newWindow)
		return;
//	if (qwe.isValid())
//		qwe->disconnect();

	CEGUI::Window *button1 = CEGUI::WindowManager::getSingleton().getWindow("maingui/b6");
	button1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainGui::exit, this));

	CEGUI::Window *button2 = CEGUI::WindowManager::getSingleton().getWindow("maingui/b1");
	button2->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainGui::newGame, this));

//	CEGUI::Event::Connection qwe = button1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Venator::GameMgr::_test, Venator::GameMgr::getSingletonPtr()));	
	
}

/*
bool MainGui::action1(const CEGUI::EventArgs &e)
{
	//const char* username = CEGUI::WindowManager::getSingleton().getWindow("window_1/usernamebox")->getText().c_str();

	const CEGUI::WindowEventArgs* args = static_cast<const CEGUI::WindowEventArgs*>(&e);
	args->window->hide();	// hide button	

    return true;
}
*/
bool MainGui::exit(const CEGUI::EventArgs &e)
{
//	gameworld->gameover = true;
	shutDown = true;
	setVisible(false);

    return true;
}


bool MainGui::newGame(const CEGUI::EventArgs &e)
{
	setVisible(false);

	LOGINFO("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
	LOGINFO("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
	LOGINFO("&&&&&&&&  NEW GAME  &&&&&&&&&");
	LOGINFO("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
	LOGINFO("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");

    return true;
}

