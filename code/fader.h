
/**

		fader effect for transitions, intro screens, ....

		fade in => show (alpha = 0 - transparent)
		fade out => disapear (alpha = 1 - no transparent)

*/


#ifndef __fader_h_
#define __fader_h_


#include <string>

#include "sigc++/sigc++.h"

namespace Ogre {
	class TextureUnitState;
	class Overlay;
}

namespace Venator {
	class Fader;
}


class Venator::Fader
{
	public:
		enum FADEROPERATION { FADE_NONE, FADE_IN, FADE_OUT};

	public:
		Fader(const std::string& overlayname, const std::string& materialname); 
		~Fader(void);
		
		// go transparent
		void setFadeIn(const double& duration = 1.0f);
		// go black (or other texture)
		void setFadeOut(const double& duration = 1.0f);

		void update(const double& dt);

		/**
			interrupts fade operations + 
			manually sets the alpha value
		*/
		void setAlpha(const double& alpha);

		/**
			interrupts fade operations + 
			hides the overlay
		*/
		void stop(void);

		/**
			interrupts fade operations + 
			eliminates the overlay
		*/
		void end(void);

		FADEROPERATION getCurrentOperation(void) { return operation; }

		sigc::signal<void> fadeoutdone;
		sigc::signal<void> fadeindone;

	private:
		double alpha;
		double current_time;
		double total_time;
		Ogre::TextureUnitState* tex_unit;
		Ogre::Overlay* overlay;
		FADEROPERATION operation;
		bool active;
		
};


#endif