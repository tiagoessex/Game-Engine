
#ifndef __ExitGui_h_
#define __ExitGui_h_


#include "BaseGui.h"


namespace Venator {	
	namespace GuiSystem	{
		class ExitGui;
	}
}

class Venator::GuiSystem::ExitGui : public BaseGui
{
	public:
		ExitGui(const std::string& name, const std::string& layout);
		~ExitGui(void);
		virtual bool loadGui(void);
		void RegisterHandlers(void);

	private:

		// actions
		bool action1(const CEGUI::EventArgs &e);
		CEGUI::Event::Connection qwe;
};



#endif
