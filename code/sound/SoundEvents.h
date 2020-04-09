
/**

*/

#ifndef __SoundEvents_H__
#define __SoundEvents_H__

//#include "SoundManager.h"
//#include "Sound.h"

#include <irrKlang.h>

namespace Venator {
	namespace SoundSystem {
		class CallbackSoundEnd;
	}
}

class Venator::SoundSystem::CallbackSoundEnd : public irrklang::ISoundStopEventReceiver {
	public:
		void OnSoundStopped (irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData);
		/*{
			if (reason == irrklang::ESEC_SOUND_FINISHED_PLAYING) {
				Sound* temp = static_cast<Sound*>(userData);
				SoundManager::getInstance()->destroySound(temp);
			}
		}*/
};


#endif