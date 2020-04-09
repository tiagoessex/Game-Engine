

#include "SoundManager.h"
#include "../Globals.h"
#include "Sound.h"
#include "SoundCommon.h"
#include "SoundEvents.h"
#include "SoundListener.h"
#include "Sound3D.h"

#include <irrKlang.h>

#include <string>

using namespace Venator;
using namespace Venator::SoundSystem;
using namespace irrklang;



SoundManager *SoundManager::mSoundManager = 0;

long double SoundManager::n_3d = 0;


SoundManager::SoundManager(void):
				engine(0),
				endcallback(0),
				listener(0)				
{}

SoundManager::~SoundManager() 
{}

bool SoundManager::initialise(void)
{

	engine = createIrrKlangDevice();
	
	if (!engine) {
		LOGERROR("!ERROR -- SoundManager [initialise] -- - unable to start device");
		return false;
	}

	endcallback = new CallbackSoundEnd();


	return true;
}



void SoundManager::destroy(void) {

	reset();

	if (endcallback)	{ delete endcallback; }
	if (listener)		{ delete listener; }
	if (engine)			{ engine->drop(); }

	if ( getInstance() ) { delete mSoundManager; }
}


void SoundManager::reset(void) {

	std::list<Sound*>::iterator it = soundstrk.begin();
	while (it != soundstrk.end()) {
		delete *it;
		soundstrk.erase(it++);
	}
	soundstrk.clear();

	if (engine) {
		engine->stopAllSounds();
		engine->removeAllSoundSources();	
	}

}



std::string SoundManager::getDriver(void) {
	return engine->getDriverName();
}

void SoundManager::setVolume(SScalar volume) { 
	engine->setSoundVolume(volume); 
};

SScalar SoundManager::getVolume(void) { 
	return engine->getSoundVolume(); 
};

void SoundManager::stopAll(void) { 
	engine->stopAllSounds(); 
};

void SoundManager::pauseAll(bool pause) { 
	engine->setAllSoundsPaused(pause); 
};


void SoundManager::setMinDistance(SScalar distance) { 
	engine->setDefault3DSoundMinDistance(distance); 
};

SScalar SoundManager::getMinDistance(void) { 
	return engine->getDefault3DSoundMinDistance(); 
};


void SoundManager::setMaxDistance(SScalar distance) { 
	engine->setDefault3DSoundMaxDistance(distance); 
};

SScalar SoundManager::getMaxDistance(void) { 
	return engine->getDefault3DSoundMaxDistance(); 
};

void SoundManager::setRolloffFactor(SScalar rolloff) { 
	engine->setRolloffFactor(rolloff); 
};

void SoundManager::setDoppler(SScalar dopplerfac, SScalar distance) { 
	engine->setDopplerEffectParameters(dopplerfac, distance); 
};


bool SoundManager::isPlaying(const std::string& filename) {
	return engine->isCurrentlyPlaying (filename.c_str());
}


void SoundManager::loadSound(const std::string& filename) {
	if(!engine->getSoundSource(filename.c_str(), false)) {
		engine->addSoundSourceFromFile(filename.c_str(), irrklang::ESM_AUTO_DETECT, true);
		LOGINFO(("sound [" + filename + "] added - file [" + filename + "]").c_str());
	} else {
		LOGERROR(("!ERROR - [SoundManager::loadSound] -- sound NOT ADDED - file [" + filename + "] ALREADY LOADED").c_str());
	}
}

void SoundManager::removeSound(const std::string& name) {
	engine->removeSoundSource(name.c_str());
}


void SoundManager::removeSound(irrklang::ISoundSource *source) {
	engine->removeSoundSource(source);
}

void SoundManager::removeAllSoundsSources(void) {
	engine->removeAllSoundSources();
}



void SoundManager::playSingleSound2D(	const char* filename, 
										bool loop, 
										SScalar volume, 
										SScalar pan)
{
	irrklang::ISound* temp = engine->play2D(filename, loop, false, true, irrklang::ESM_AUTO_DETECT,true);
	temp->setVolume(volume);
	temp->setPan(pan);
	temp->drop();	
}




Sound* SoundManager::createSound2D(	const char* soundname, 
										bool loop,
										SScalar volume,
										SScalar pan,
										bool hooked) 
{
	irrklang::ISoundSource *source = engine->getSoundSource(soundname, false);

	if(source) {
		irrklang::ISound* temp = engine->play2D(source, loop, true, true, false);
		temp->setVolume(volume);
		temp->setPan(pan);	
		Sound* s = new Sound(temp);	
		soundstrk.push_back(s);
		
		if (hooked) { temp->setSoundStopEventReceiver(endcallback, (void *) s); }

		return s;
	} else {
		LOGERROR(("!ERROR - [SoundManager::createSound2D] -- - unable to play sound [" + 
				std::string(soundname) + " - sound do not exist").c_str());
	}
	return 0;
}

Sound3D* SoundManager::createSound3D(	const char* soundname,
										const Vec3& pos,
										bool loop,
										SScalar volume,
										SScalar pan,
										bool hooked)
{
	irrklang::ISoundSource *source = engine->getSoundSource(soundname, false);

	if(source) {		
		irrklang::ISound* temp = engine->play3D(source, Vec3Sound(pos), loop, true,true, false);	
		temp->setVolume(volume);
		temp->setPan(pan);	
		Sound3D* s = new Sound3D(temp);	
		soundstrk.push_back(s);
		
		if (hooked) { temp->setSoundStopEventReceiver(endcallback, (void *) s); }

		return s;
	} else {
		LOGERROR(("!ERROR - [SoundManager::createSound3D] -- - unable to play sound [" + 
				std::string(soundname) + " - sound do not exist").c_str());
	}
	return 0;
}


void SoundManager::destroySound(Sound* s) {
	std::list<Sound*>::iterator it;
	for (it = soundstrk.begin(); it != soundstrk.end(); it++)  {
		if ((*it) == s) {
			delete *it;
			soundstrk.erase(it);
			return;
		}
	}
}

SoundListener* SoundManager::createListener(	const Vec3& pos,
												const Vec3& lookdir,
												const Vec3& velPerSecond,
												const Vec3& upVector)
{
	if (listener) { delete listener; listener = 0; }
	listener = new SoundListener(engine);
	listener->setListenervalues(pos,lookdir,velPerSecond,upVector);
	return listener;
}
		


SoundManager* SoundManager::getInstance( void ) {
	if( !mSoundManager ) {
		mSoundManager = new SoundManager();
    }

    return mSoundManager;
}
