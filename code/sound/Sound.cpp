

#include "Sound.h"

using namespace Venator;
using namespace Venator::SoundSystem;
using namespace irrklang;


int Sound::ID = 0;

Sound::Sound(irrklang::ISound* sound):
					id(ID),
					mSound(sound)
{ ID++; };

Sound::~Sound() { 
	if (mSound) {
		mSound->stop();
		mSound->drop();
		mSound = 0;
	}
};

void Sound::play(void) {
	if (!mSound) { return; }
	mSound->setIsPaused(false);
};

void Sound::stop(void) {
	if (!mSound) { return; }
	mSound->stop(); 
};

void Sound::pause(bool pause) {
	if (!mSound) { return; }
	mSound->setIsPaused(pause);
}

void Sound::setVolume(SScalar volume) { 
	if (!mSound) { return; }
	mSound->setVolume(volume); 
};

void Sound::setPan(SScalar pan) { 
	if (!mSound) { return; }
	mSound->setPan(pan); 
};





