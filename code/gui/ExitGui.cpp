
#include "ExitGui.h"
#include "../Globals.h"


using namespace Venator;
using namespace Venator::GuiSystem;

ExitGui::ExitGui(const std::string& name, const std::string& layout) :
				BaseGui(name, layout),
				qwe(0)

{}



ExitGui::~ExitGui(void)
{}

bool ExitGui::loadGui(void)
{
	if (!BaseGui::loadGui()) {
		LOGERROR(("!ERROR -- ExitGui -- - CAN'T LOAD LAYOUT [" + layout + "] FOR ExitGui [" + name + "]").c_str());
		return false;
	}
	RegisterHandlers();
	return true;
}


void ExitGui::RegisterHandlers(void)	// param: gamestate* and call this inside gamestate after calling setvisible
{
	if (!newWindow) { return; }
	//if (qwe.isValid())
	//	qwe->disconnect();
	//CEGUI::Window *button1 = CEGUI::WindowManager::getSingleton().getWindow("window_1/b1");
	//button1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainGui::action1, this));
	//CEGUI::Event::Connection qwe = button1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Venator::GameMgr::_test, Venator::GameMgr::getSingletonPtr()));	
	
}


bool ExitGui::action1(const CEGUI::EventArgs &e)
{
	//const char* username = CEGUI::WindowManager::getSingleton().getWindow("window_1/usernamebox")->getText().c_str();

	const CEGUI::WindowEventArgs* args = static_cast<const CEGUI::WindowEventArgs*>(&e);
	args->window->hide();	// hide button	

    return true;
}
