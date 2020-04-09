
/**

	
		BaseGui* maingui;
		BaseGui* exitgui;
		// load guis
		maingui = new MainGui("maingui","maingui.layout");
		if (!maingui->loadGui())
		{
			delete maingui;
			maingui = 0;
		}
		exitgui = new ExitGui("exitgui","exitgui.layout");
		if (!exitgui->loadGui())
		{
			delete exitgui;
			exitgui = 0;
		}

		...

		
		if (maingui)
			delete maingui;
		if (exitgui)
			delete exitgui;


*/


#ifndef __BaseGui_h_
#define __BaseGui_h_


#include <CEGUI.h>
#include <string>

namespace Venator {
	namespace GuiSystem	{
		class BaseGui;
	}
}

class Venator::GuiSystem::BaseGui
{
	public:
		BaseGui(const std::string& name, const std::string& layout);
		virtual ~BaseGui(void);
		virtual bool loadGui(void);
		void setVisible(bool);
		bool isVisible(void);

		const std::string& getName(void) { return name; };
		//virtual void _RegisterHandlers(void) = 0;

	protected:				
		std::string name;
		std::string layout;
		CEGUI::Window *newWindow;
};



#endif
