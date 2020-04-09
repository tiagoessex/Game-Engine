
/**
		transforms: Scale
		

	PARAMETERS:
		- [scale]	- "x,y,z" scale (default: 1.0,1.0,1.0)

*/


#ifndef __ComponentScale_H__
#define __ComponentScale_H__

#include "Component.h"
//#include "../../Globals.h"
#include "../../Prerequisites.h"

namespace Venator {	
	namespace GameObjectComponentSystem {
		class ComponentScale;
	}
}

class Venator::GameObjectComponentSystem::ComponentScale : public Component {

	public:
		Vec3 scale;		// public to inc perf

	public:
		ComponentScale(void) :  
							Component("scale"),
							scale(Vec3::UNIT_SCALE)
		{ 
			//LOGTORS("ComponentScale CTOR");
		};

		~ComponentScale(void) { 
			//LOGTORS("ComponentScale DTOR");
		};

		void start();

		void setSX(const Scalar& x)	{
			scale.x = x;
		}

		void setSY(const Scalar& y)	{
			scale.y = y;
		}


		void setSZ(const Scalar& z)	{
			scale.z = z;
		}

		
		void setScale(const Scalar& x, const Scalar& y, const Scalar& z) {
			scale.x = x;
			scale.y = y;
			scale.z = z;
		}

		void setScale(const Vec3& s) {
			scale = s;
		}


		const Scalar& getSX(void) {
			return scale.x;
		}

		const Scalar& getSY(void) {
			return scale.y;
		}

		const Scalar& getSZ(void) {
			return scale.z;
		}

		const Vec3& getScale(void) {
			return scale;
		}


		static Factory<Component,ComponentScale> compFactory;

};	// class ComponentScale


#endif