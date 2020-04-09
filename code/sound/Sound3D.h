


#ifndef __Sound3D_H__
#define __Sound3D_H__


// c/c++ headers
#include <string>


// irrklang
//#include <irrKlang.h>

// venator libs
//#include "SoundCommon.h"
#include "SoundManager.h"
#include "Sound.h"


namespace Venator {		
	namespace SoundSystem {
		class Sound3D;
	}
}
class Venator::SoundSystem::Sound3D : public Sound {

	friend class SoundManager;

	protected:
		Sound3D(irrklang::ISound* sound);
		~Sound3D();

	public:

		void setMaxDistance(const SScalar& distance);
		void setMinDistance(const SScalar& distance);

		void setPosition(const Vec3& pos);
		void setVelocity(const Vec3& vel);

		Vec3 getPosition(void) { return SoundVec3(mSound->getPosition()); };		

		irrklang::ISound* getSound(void) { return mSound; };		
};






#endif