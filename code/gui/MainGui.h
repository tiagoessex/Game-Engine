
#ifndef __MainGui_h_
#define __MainGui_h_


#include "BaseGui.h"


namespace Venator {
	namespace GuiSystem	{
		class MainGui;
	}
}

class Venator::GuiSystem::MainGui : public BaseGui
{
	public:
		MainGui(const std::string& name, const std::string& layout);
		~MainGui(void);
		virtual bool loadGui(void);
		void RegisterHandlers(void);

	private:		

		// actions
		bool exit(const CEGUI::EventArgs &e);
		bool newGame(const CEGUI::EventArgs &e);

		//CEGUI::Event::Connection qwe;
};

#endif
