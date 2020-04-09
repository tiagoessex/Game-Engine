

/*
	---
	SoundManager::getSingletonPtr()->initialise();
	---
	SoundManager::getSingletonPtr()->loadSound("C:/sounds/explosion.wav");
	---

	// single 2d sound => play + destroy
	SoundManager::getSingletonPtr()->playSingleSound("C:/sounds/explosion.wav");

	// 2d sound
	Sound* s = SoundManager::getSingletonPtr()->createSound2D("C:/sounds/explosion.wav", true);	
	s->play();
	s->setVolume(1.0);
	SoundSystem::SoundManager::getSingletonPtr()->destroySound(s);	// optional

	// 3d sound		
	Sound3D* s = SoundManager::getSingletonPtr()->createSound3D("C:/sounds/musik.ogg",Vec3(0,0,0));
	s->play();
	...
	s->setPosition(Vec3(0,0,4));
	...
	s->setPosition(Vec3(0,0,-4));
	...


	---

	SoundSystem::SoundManager::getSingletonPtr()->destroy();

*/


#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__


#include <list>

//#include <irrKlang.h>

#include "SoundCommon.h"

namespace irrKlang {
	class ISoundEngine;
}

namespace Venator {	
	namespace SoundSystem { 		
		class SoundManager;
		class Sound;
		class CallbackSoundEnd;
		class SoundListener;
		class Sound3D;
	}
}

class Venator::SoundSystem::SoundManager {
	public:

		bool initialise(void); 
		void destroy(void);  
		void reset(void);

		/**
			get engine sound - in case user requires low level control
		*/
		irrklang::ISoundEngine* getEngine(void) { return engine; };

		/**
			return the audio driver been used
			in windows is normallu DirectSound
		*/
		std::string getDriver(void);

		// engine settings
		void setVolume(SScalar volume);
		SScalar getVolume(void);
		void stopAll(void);
		void pauseAll(bool pause = true);
		void setMinDistance(SScalar distance);
		SScalar getMinDistance(void);
		void setMaxDistance(SScalar distance);
		SScalar getMaxDistance(void);
		void setRolloffFactor(SScalar rolloff);
		void setDoppler(SScalar dopplerfac = 1.0f, SScalar distance = 1.0f) ;
		bool isPlaying(const std::string& filename);	


		// pre load
		void loadSound(const std::string& filename);// pre load sound
		void removeSound(const std::string& name);
		void removeSound(irrklang::ISoundSource *source);
		void removeAllSoundsSources(void);
		
		// hooked => on end emit event

		// 2d sounds
		// play once and gone
		void playSingleSound2D(	const char* filename, 
								bool loop = false,
								SScalar volume = 0.75f,
								SScalar pan = 0.0f);

	
		Sound* createSound2D(	const char* soundname, 
								bool loop = false,
								SScalar volume = 0.75f,
								SScalar pan = 0.0f,
								bool hooked = false);

		Sound3D* createSound3D(	const char* soundname,
								const Vec3& pos,
								bool loop = false,
								SScalar volume = 0.75f,
								SScalar pan = 0.0f,
								bool hooked = false);

		void destroySound(Sound* s);
		

		// listener
		SoundListener* createListener(	const Vec3& pos = Venator::Vec3(0, 0, 0),
										const Vec3& lookdir = Venator::Vec3(0, 0, 1),
										const Vec3& velPerSecond = Venator::Vec3(0, 0, 0),
										const Vec3& upVector = Venator::Vec3(0, 1, 0));
		
		SoundListener* getListener(void) { return listener; }


		static SoundManager* getInstance( void );

	private:
		SoundManager(void);
		~SoundManager(void);
		SoundManager(SoundManager const&);
		void operator=(SoundManager const&);
		static SoundManager *mSoundManager;				
		
		irrklang::ISoundEngine* engine;	// irrklang engine	

		std::list<Sound*> soundstrk;
		CallbackSoundEnd* endcallback;
		SoundListener* listener;

		static long double n_3d;
		
		

};


 #endif /*__SOUNDMANAGER_H__*/