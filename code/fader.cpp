

#include "fader.h"

#include "OgreMaterialManager.h"
#include "OgreOverlayManager.h"
#include "OgreTechnique.h"
#include "OgreBlendMode.h"

#include "OgreOverlayContainer.h"

#include "Globals.h"

using namespace Ogre;
using namespace Venator; 


Fader::Fader(	const std::string& overlayname, 
				const std::string& materialname):
				tex_unit(0),
				overlay(0),
				alpha(0),
				current_time(0),
				total_time(0),
				operation(FADE_NONE),
				active(false)
{
	try	{
		// get the material
		Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName(materialname);
		Ogre::Technique *tech = mat->getTechnique(0); 
		Ogre::Pass *pass = tech->getPass(0); 
		tex_unit = pass->getTextureUnitState(0);

		// get the overlay
		overlay = Ogre::OverlayManager::getSingleton().getByName(overlayname);
		overlay->hide();
				
		alpha = 0.0f;
		current_time = 0.0f;
		total_time = 0.0f;
		operation = FADE_NONE;
		active = true;

	} catch (Ogre::Exception e) {
		LOGERROR("ERROR! - Fader - UNABLE TO SETUP SHITS");
	}

}


Fader::~Fader(void)
{
/*	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
		overlayManager.getOverlayElement("FadeInOutPanel"));
	overlay->remove2D(panel);	
	Ogre::OverlayManager::getSingleton().destroyOverlayElement(panel);
 	Ogre::OverlayManager::getSingleton().destroy(overlay);
*/
}



void Fader::setFadeIn(const double& duration)
{
	operation = FADE_IN;
	alpha = 0.0f;
	current_time = abs(duration);
	total_time = abs(duration);
	overlay->show();
}


void Fader::setFadeOut(const double& duration)
{
	operation = FADE_OUT;
	alpha = 1.0f;
	current_time = 0.0f;
	total_time = abs(duration);
	overlay->show();
}


void Fader::setAlpha(const double& alpha)
{
	tex_unit->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, alpha);
	operation = FADE_NONE;
}


void Fader::stop(void)
{
	overlay->hide();
	operation = FADE_NONE;
/*	if (operation != FADE_NONE) {
		overlay->hide();
		operation = FADE_NONE;
	}*/
}

void Fader::end(void) 
{
	// overlay->hide();
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
		overlayManager.getOverlayElement("FadeInOutPanel"));
	overlay->remove2D(panel);	
	Ogre::OverlayManager::getSingleton().destroyOverlayElement(panel);
 	Ogre::OverlayManager::getSingleton().destroy(overlay);
}

void Fader::update(const double& timeSinceLastFrame)
{	
	if (!active) return;
	if (operation == FADE_IN) {
		current_time -= timeSinceLastFrame;
		alpha = current_time / total_time;
		if (alpha < 0.0f) {
			operation = FADE_NONE;
			overlay->hide();
			fadeindone.emit();
		} else {
			tex_unit->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, alpha);	
		}
	} else if (operation == FADE_OUT) {
		current_time += timeSinceLastFrame;
		alpha = current_time / total_time;
		if (alpha > 1.0f) {
			operation = FADE_NONE;
			fadeoutdone.emit();
		} else {
			tex_unit->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, alpha); 
		}
	}
}
