

/**
		sound listener
*/



#ifndef __SoundListener_H__
#define __SoundListener_H__

// venator libs
#include "SoundCommon.h"



// irrklang
#include <irrKlang.h>



namespace Venator {		
	namespace SoundSystem { 
		class SoundListener;
	}
}

class Venator::SoundSystem::SoundListener {
	friend class SoundManager;

	private:
		irrklang::ISoundEngine* engine;
		Vec3 listener_position;
		Vec3 listener_direction;
		Vec3 listener_velocity;
		Vec3 listener_upvector;

	protected:
		SoundListener(irrklang::ISoundEngine* engine);

	public:
		~SoundListener(void);

		void setListenervalues(	const Vec3& pos,
								const Vec3& lookdir,
								const Vec3& velPerSecond,
								const Vec3& upVector);

		void setPosition(const Vec3& new_pos);
		void setVelocity(const Vec3& new_vel);
		void setDirection(const Vec3& new_dir);
		void setUpvector(const Vec3& new_uvec);

		const Vec3& getPosition(void) { return listener_position; };		
		const Vec3& getDirection(void) { return listener_direction; };		
		const Vec3& getVelocity(void) { return listener_velocity; };		
		const Vec3& getUpVector(void) { return listener_upvector; };		

};






#endif