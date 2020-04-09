

#include "Sound3D.h"


using namespace Venator;
using namespace Venator::SoundSystem;
using namespace irrklang;
using namespace std;

Sound3D::Sound3D(ISound* sound) :
					Sound(sound)					
{};

Sound3D::~Sound3D() 
{};

void Sound3D::setMaxDistance(const SScalar& distance) { 
	if (!mSound) { return; }
	mSound->setMaxDistance(distance); 
};

void Sound3D::setMinDistance(const SScalar& distance) { 
	if (!mSound) { return; }
	mSound->setMinDistance(distance); 
};

void Sound3D::setPosition(const Vec3& pos) { 
	if (!mSound) { return; }
	mSound->setPosition(Vec3Sound(pos));
};

void Sound3D::setVelocity(const Vec3& vel) { 
	if (!mSound) { return; }
	mSound->setVelocity(Vec3Sound(vel)); 
};




