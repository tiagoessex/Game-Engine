

#include "ComponentText2D.h"
#include "../../Globals.h"
#include "../../VenatorUtils.h"
//#include "../ComponentsManager.h"

#include "OgreTextAreaOverlayElement.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
//#include "OgreColourValue.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;

int ComponentText2D::ID = 0;

ComponentText2D::ComponentText2D(	const std::string& caption, 
									const std::string& fontname, 
									Scalar size, 
									Scalar x, 
									Scalar y, 
									Scalar size_x, 
									Scalar size_y, 
									Scalar text_x, 
									Scalar text_y) :  
							Component("Text2D"),
							caption(caption),
							panel(0),
							fontname(fontname),
							size(size),
							textArea(0),
							overlay(0)
					
{
	name = "go_component_text2d_" + Number2String(ID++);

	LOGTORS("************ ComponentText2D CTOR ************");	

	ID++;

	// set container

	// Create a panel where text container will be
	panel = static_cast<Ogre::OverlayContainer*>(  Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "Panel_" + name));
	//panel->setMetricsMode(Ogre::GMM_PIXELS);//GMM_RELATIVE);
	panel->setMetricsMode(Ogre::GMM_RELATIVE);
	panel->setPosition(x,y);
	panel->setDimensions(size_x,size_y);		// screen width/height
	// Create an overlay, and add the panel
	overlay =  Ogre::OverlayManager::getSingletonPtr()->create(name);
	overlay->add2D(panel);
	

	// set text container

	// Create a text area
	textArea = static_cast<Ogre::TextAreaOverlayElement*>( Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("TextArea", name));
	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	//textArea->setPosition(x,y);
	//textArea->setDimensions(size_x, size_y);
	textArea->setPosition(text_x,text_y);
	textArea->setDimensions(1,1);
	textArea->setCharHeight(size);
	textArea->setFontName(fontname);	
	// Add the text area to the panel
	panel->addChild(textArea);
	
	// Show the overlay
	overlay->show();

	textArea->setCaption(caption);
}


ComponentText2D::~ComponentText2D(void)
{
	LOGTORS("************ ComponentText2D DTOR ************");
	
	overlay->hide();
	//panel->removeChild(name);
	panel->removeChild(name);
	overlay->remove2D(panel);
	Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(name);			
	Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(panel);
	Ogre::OverlayManager::getSingletonPtr()->destroy(overlay);
	//Ogre::OverlayManager::getInstance()->destroy(name);

}


void ComponentText2D::setCaption(const std::string& msg)
{	
	textArea->setCaption(msg);
}

void ComponentText2D::setVisible(bool v)
{
	if (v)
		overlay->show();
	else
		overlay->hide();
}

bool ComponentText2D::getVisible(void)
{
	return overlay->isVisible();
}

void ComponentText2D::setTextSize(Scalar newsize)
{
	textArea->setCharHeight(newsize);
}


void ComponentText2D::setColour(const Ogre::ColourValue& colour)
{
	textArea->setColour(colour);
}

void ComponentText2D::setUpperColour(const Ogre::ColourValue& colour)
{
	textArea->setColourTop(colour);
}

void ComponentText2D::setBottonColour(const Ogre::ColourValue& colour)
{
	textArea->setColourBottom(colour);
}

void ComponentText2D::setBackgroundMaterial(const std::string& material)
{
	panel->setMaterialName(material);
}




