


#include "BaseGui.h"

#include "../Globals.h"


using namespace Venator;
using namespace Venator::GuiSystem;

BaseGui::BaseGui(const std::string& name, const std::string& layout):
						name(name),
						layout(layout),
						newWindow(0)

{}

bool BaseGui::loadGui(void)
{
	if (!CEGUI::WindowManager::getSingletonPtr()) {

		LOGERROR(("!ERROR -- BaseGui -- - can't load GUI1 -- " + name + " -- :windowmanager is NULL").c_str());
		return false;
	}

	try {
		newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout(layout);
		//newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout(layout,"second_");
		CEGUI::System::getSingleton().getGUISheet()->addChildWindow(newWindow);
		//RegisterHandlers();
	} catch (std::exception ex)	{
		LOGERROR(("!ERROR -- BaseGui -- - CAN'T LOAD LAYOUT [" + layout + "] FOR BaseGui [" + name + "]").c_str());
		newWindow = 0;
		return false;
	}


	LOGINFO(("layout for BaseGui [" + layout + "] loaded - [" + name + "]").c_str());

	newWindow->setVisible(false);

	return true;
}


BaseGui::~BaseGui(void)
{
	CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(newWindow);
	CEGUI::WindowManager::getSingleton().destroyWindow(newWindow);
}


void BaseGui::setVisible(bool what)
{
	if (newWindow) {
		newWindow->setVisible(what);
	}
}


bool BaseGui::isVisible(void)
{
	if (newWindow) {
		return newWindow->isVisible();
	}
	return false;
}

