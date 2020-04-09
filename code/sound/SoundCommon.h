


#ifndef __SoundCommon_H__
#define __SoundCommon_H__

// venator
#include "../Prerequisites.h"

#include <irrKlang.h>


namespace Venator {
	typedef irrklang::ik_f32 SScalar;

	inline irrklang::vec3df Vec3Sound(const Vec3& V) {
		return irrklang::vec3df(V.x, V.y, V.z);
	}
 
	inline Vec3 SoundVec3(const irrklang::vec3df& V) {
		return Vec3(V.X, V.Y, V.Z);
	}
}

#endif


