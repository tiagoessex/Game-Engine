
/**
	prerequisites: global typedefs

	Ogre::Vector2		-> Vec2(x,y)
	Ogre::Vector3		-> Vec3(x,y,z)
	Ogre::Quaternion	-> Quat(w,x,y,z)
	Ogre::Real			-> Scalar

	remarks:
		- to avoid Ogre3d dependence spread among modules and to harmonize all modules
			- any module can be detached from ogre dependence by just:
					typedef new_shit Scalar;	// where new_shit could be Scalar
					

*/

#ifndef __Prerequisites_H__
#define __Prerequisites_H__


// ogre headers
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreColourValue.h>

namespace Venator {


	/**
		define int32_t and uint32_t types.
		@remarks
			windows platafforms, namely ms c++ does not define these types anymore.
			necessary for the isBigIndian function
	*/
	#if WIN32
		typedef __int32 int32_t;
		typedef unsigned __int32 uint32_t;
	#endif


	/**
		ogre | venator types
	*/
	typedef Ogre::Vector2 Vec2;
	typedef Ogre::Vector3 Vec3;
	typedef Ogre::Quaternion Quat;
	typedef Ogre::Real Scalar;
	typedef Ogre::ColourValue Color;
	

	struct POTransform {
		POTransform(const Vec3& pos, const Quat& quat) : position(pos), orientation(quat) {} ;
		POTransform(void) : position(Vec3(0,0,0)), orientation(Quat(1,0,0,0)) {} ;
		Vec3 position;
		Quat orientation;		
	};


	struct PSOTransform	{
		Vec3 position;
		Vec3 scale;
		Quat orientation;
	};
	
}

#endif


