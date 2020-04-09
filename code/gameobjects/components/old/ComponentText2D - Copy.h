
/**
		2d text based on overlay
		since this component does not depend on managers and nodes
		all init / final / usage code is done here


		ex:

			new ComponentText2D("qdeasdasd","debug",16,0,0,0.125f,0.1666f,400,50));


*/


#ifndef __ComponentText2D_H__
#define __ComponentText2D_H__

#include "Component.h"
#include "../../Prerequisites.h"


namespace Ogre
{
	class OverlayContainer;
	class Overlay;
	class TextAreaOverlayElement;
}

namespace Venator
{

	namespace GameObjectComponentSystem
	{

		class ComponentText2D : public Component
		{
			private:
				std::string fontname;
				std::string caption;
				std::string material;
				std::string name;
				Scalar size;

				Ogre::OverlayContainer* panel;
				Ogre::Overlay* overlay;
				Ogre::TextAreaOverlayElement* textArea;
				
			public:
				ComponentText2D(	const std::string& caption, 
									const std::string& fontname, 
									Scalar size, 
									Scalar x, 
									Scalar y, 
									Scalar size_x, 
									Scalar size_y, 
									Scalar text_x = 0, 
									Scalar text_y = 0);
				~ComponentText2D(void);			

				void setCaption(const std::string& msg);
				const std::string& getCaption(void) { return caption; };

				void setVisible(bool v);
				bool getVisible(void);

				void setTextSize(Scalar newsize);
		
				void setColour(const Ogre::ColourValue& colour);
				void setUpperColour(const Ogre::ColourValue& colour);
				void setBottonColour(const Ogre::ColourValue& colour);
				void setBackgroundMaterial(const std::string& material);


				static int ID;

		};	// class ComponentText2D

	}		// namespace GameObjectComponentSystem

}			// namespace venator


#endif