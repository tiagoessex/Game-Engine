
/**

	static text class

		used just for 1 instance
		can dynamically change:
			- caption
			- size
			- colours
			- background material
			- visibility

		notes:
			- no visible memory leak????????????

	usage:

		tx2 = new StaticText("fuck","font1",0.03,0.8f,0);
	
		tx2->setText("mother fucker");
		tx2->setVisible(true);

		...

		delete tx2;

		if not show text:

		// load/reload font before 
		Ogre::FontManager::getSingleton().getByName("font1")->load();

*/


#ifndef __StaticText_h_
#define __StaticText_h_


// venator headers
#include "../Prerequisites.h"		// Scalar type


// ogre headers
#include "OgrePrerequisites.h"	// Ogre::ColourValue

namespace Ogre {
	class OverlayContainer;
	class Overlay;
	class TextAreaOverlayElement;
}

namespace Venator {
	namespace RenderEngine {
		class StaticText;
	}
}

class Venator::RenderEngine::StaticText {

	public:
		/**
			name - unique name for each instance
			fontname
			x,y, size_x, size_y - rect dim ((0,0) -> (1,1))
			text_x, text_y - tex tpos relatitveluy to x,y (in pixels)
		*/
		StaticText(const std::string& caption, const std::string& fontname, 
			Scalar size, Scalar text_x = 0, Scalar text_y = 0);
		~StaticText(void);
		void setCaption(const std::string &msg);
		std::string getCaption(void);

		void setVisible(bool v);
		void setTextSize(Scalar newsize);
		bool isVisible(void);

		void setColour(const Ogre::ColourValue& colour);
		void setUpperColour(const Ogre::ColourValue& colour);
		void setBottonColour(const Ogre::ColourValue& colour);

		void setBackgroundMaterial(const std::string& material);

	private:
		std::string name;
		Ogre::OverlayContainer* panel;
		Ogre::Overlay* overlay;
		std::string fontname;
		Scalar size;
		Ogre::TextAreaOverlayElement* textArea;

		static int ID;
};


#endif
