
/**
		convertions and types

		used in case others libs are included => 
				no need to change any other module


				Venator::transforms <-> bulletphysics::transforms


*/



#ifndef __BulletPhysicsPrerequisites_h_
#define __BulletPhysicsPrerequisites_h_

// venator headers
#include "../Prerequisites.h"

// bullet headers
#include <btBulletDynamicsCommon.h>

// ogre headers
#include <OgreVector3.h>
#include <OgreQuaternion.h>



namespace Venator {
	namespace PhysicsSystem	{


		inline btVector3 Vec3Physics(const Vec3& V) {
			return btVector3(V.x, V.y, V.z);
		}
 
		inline Vec3 PhysicsVec3(const btVector3& V)	{
			return Ogre::Vector3(V.x(), V.y(), V.z());
		}
 
		inline btQuaternion QuatPhysics(const Quat& Q) {
			return btQuaternion(Q.x, Q.y, Q.z, Q.w);
		};
 
		inline Quat PhysicsQuat(const btQuaternion& Q) {
			return Quat(Q.w(), Q.x(), Q.y(), Q.z());
		};

		inline btTransform TransPhysics(const POTransform& Q) {
			return btTransform(QuatPhysics(Q.orientation),Vec3Physics(Q.position));
		};

		inline POTransform PhysicsTrans(const btTransform& Q) {
			POTransform temp(PhysicsVec3(Q.getOrigin()), PhysicsQuat(Q.getRotation()));
			//temp.orientation = PhysicsQuat(Q.getRotation());
			//temp.position = PhysicsVec3(Q.getOrigin()); 
			return temp;
		};

		//typedef std::map<std::string, std::string> STRINGMAP;

	}

}

#endif
