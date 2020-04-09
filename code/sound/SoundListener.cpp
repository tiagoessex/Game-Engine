

#include "SoundListener.h"


using namespace Venator;
using namespace Venator::SoundSystem;
using namespace irrklang;
using namespace std;

SoundListener::SoundListener(ISoundEngine* engine) :
								engine(engine)


{}

SoundListener::~SoundListener() 
{};

void SoundListener::setListenervalues(	const Vec3& pos,
										const Vec3& lookdir,
										const Vec3& velPerSecond,
										const Vec3& upVector)
{
	engine->setListenerPosition(Vec3Sound(pos),Vec3Sound(lookdir),Vec3Sound(velPerSecond),Vec3Sound(upVector));
	listener_position = pos;
	listener_direction = lookdir;
	listener_velocity = velPerSecond;
	listener_upvector = upVector;	
};

void SoundListener::setPosition(const Vec3& new_pos)
{
	listener_position = new_pos;
	engine->setListenerPosition(Vec3Sound(listener_position),Vec3Sound(listener_direction));		
	
}

void SoundListener::setVelocity(const Vec3& new_vel)
{
	listener_velocity = new_vel;
	engine->setListenerPosition(Vec3Sound(listener_position),Vec3Sound(listener_direction),Vec3Sound(listener_velocity));	
}

void SoundListener::setDirection(const Vec3& new_dir)
{
	listener_direction = new_dir;
	engine->setListenerPosition(Vec3Sound(listener_position),Vec3Sound(listener_direction));	
}

void SoundListener::setUpvector(const Vec3& new_uvec)
{
	listener_upvector = new_uvec;
	engine->setListenerPosition(Vec3Sound(listener_position),Vec3Sound(listener_direction),Vec3Sound(listener_velocity),Vec3Sound(listener_upvector));
}


