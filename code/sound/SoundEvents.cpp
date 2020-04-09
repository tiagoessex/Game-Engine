


#include "SoundManager.h"
#include "SoundEvents.h"



using namespace Venator::SoundSystem;



void CallbackSoundEnd::OnSoundStopped (irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData) {
	if (reason == irrklang::ESEC_SOUND_FINISHED_PLAYING) {
		Sound* temp = static_cast<Sound*>(userData);
		SoundManager::getInstance()->destroySound(temp);
	}
}

