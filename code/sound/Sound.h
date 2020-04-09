


#ifndef __Sound_H__
#define __Sound_H__


#include <irrKlang.h>

#include "SoundCommon.h"


namespace Venator {		
	namespace SoundSystem { 
		class Sound;
	}
}

class Venator::SoundSystem::Sound
{

	friend class SoundManager;

	protected:
		irrklang::ISound* mSound;	
		int id;
		static int ID;


		Sound(irrklang::ISound* sound);	
		virtual ~Sound();

	public:

		void play(void);
		void stop(void);
		void pause(bool pause = false);
		void setVolume(SScalar volume);
		void setPan(SScalar pan);

		bool isFinished() { return mSound->isFinished(); };
		bool isPaused() { return mSound->getIsPaused(); };
		bool isLooped() { return mSound->isLooped(); };

		irrklang::ISound* getSound(void) { return mSound; };

		int getID(void) const { return id;};

};






#endif