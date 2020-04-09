


#include "StaticText.h"
//#include "../Globals.h"


#include "OgreTextAreaOverlayElement.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreStringConverter.h"
#include "OgreFontManager.h"

using namespace Venator;
using namespace Venator::RenderEngine;

int StaticText::ID = 0;

StaticText::StaticText(	const std::string& caption, 
						const std::string& fontname, 
						Scalar size, 
						Scalar text_x, Scalar text_y):
				panel(0),
				fontname(fontname),
				size(size),
				textArea(0),
				overlay(0)
{
	name = "static_text_" + Ogre::StringConverter().toString(ID);	

	// set container
	if (ID == 0) {
		// Create a panel where text container will be
		panel = static_cast<Ogre::OverlayContainer*>(  Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "text_stuff"));
		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(0,0);
		panel->setDimensions(1.0f, 1.0f);		// screen width/height
		overlay =  Ogre::OverlayManager::getSingletonPtr()->create("text_stuff_overlay");
		overlay->add2D(panel);
	}

	ID++;

	overlay=Ogre::OverlayManager::getSingletonPtr()->getByName("text_stuff_overlay");
	panel=static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("text_stuff"));
	
	//LOGINFO(("OVERLAY -> " + Ogre::StringConverter().toString(overlay)).c_str());
	//LOGINFO(("PANEL -> " + Ogre::StringConverter().toString(overlay)).c_str());

	textArea = static_cast<Ogre::TextAreaOverlayElement*>( Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("TextArea", name));	
	textArea->setMetricsMode(Ogre::GMM_RELATIVE);//GMM_PIXELS);	
	textArea->setPosition(text_x,text_y);
	textArea->setDimensions(1,1);
	textArea->setCharHeight(size);
	Ogre::FontManager::getSingleton().getByName(fontname)->load();
	textArea->setFontName(fontname);
	textArea->setCaption(caption);

	panel->addChild(textArea);	

	overlay->show();
	
}



StaticText::~StaticText(void) 
{
	
	panel->removeChild(name);
	Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(name);
	ID--;
	if(ID == 0) {
		overlay->remove2D(panel);
		Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement("text_stuff");
		Ogre::OverlayManager::getSingletonPtr()->destroy("text_stuff_overlay");
	}

//	overlay->hide();
	//panel->removeChild(name);
	/*panel->removeChild(name);
	overlay->remove2D(panel);
	Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(name);			
	Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(panel);
	Ogre::OverlayManager::getSingletonPtr()->destroy(overlay);
	*/
	//Ogre::OverlayManager::getInstance()->destroy(name);
}

void StaticText::setCaption(const std::string& msg) 
{	
	textArea->setCaption(msg);
}

std::string StaticText::getCaption(void)
{
	return textArea->getCaption();
}

void StaticText::setVisible(bool v)
{
	if (v) {
		overlay->show();
	} else {
		overlay->hide();
	}
}

bool StaticText::isVisible(void) 
{
	return overlay->isVisible();
}

void StaticText::setTextSize(Scalar newsize)
{
	textArea->setCharHeight(newsize);
}


void StaticText::setColour(const Ogre::ColourValue& colour)
{
	textArea->setColour(colour);
}

void StaticText::setUpperColour(const Ogre::ColourValue& colour) 
{
	textArea->setColourTop(colour);
}

void StaticText::setBottonColour(const Ogre::ColourValue& colour) 
{
	textArea->setColourBottom(colour);
}

void StaticText::setBackgroundMaterial(const std::string& material) 
{
	panel->setMaterialName(material);
}