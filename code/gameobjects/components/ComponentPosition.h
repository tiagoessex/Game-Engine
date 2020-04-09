
/**
		transforms: Position

	PARAMETERS:
		- [position]	- "x,y,z"	(default: 0,0,0)


*/


#ifndef __ComponentPosition_H__
#define __ComponentPosition_H__

#include "Component.h"
#include "../../Prerequisites.h"


namespace Venator {	
	namespace GameObjectComponentSystem	{
		class ComponentPosition;
	}
}
class Venator::GameObjectComponentSystem::ComponentPosition : public Component {

	public:
		Vec3 position;		// as public to inc performance

	public:
		ComponentPosition(void) :  
							Component("position"),
							position(Vec3::ZERO) 
		{ 
		};

		~ComponentPosition(void) {};

		void start(void);

		void setX(const Scalar& x) {
			position.x = x;
		}

		void setY(const Scalar& y) {
			position.y = y;
		}


		void setZ(const Scalar& z) {
			position.z = z;
		}

		
		void setPosition(const Scalar& x, const Scalar& y, const Scalar& z) {
			position.x = x;
			position.y = y;
			position.z = z;
		}

		void setPosition(const Vec3& v3) {
			position = v3;
		}

		const Scalar& getX(void) {
			return position.x;
		}

		const Scalar& getY(void) {
			return position.y;
		}

		const Scalar& getZ(void) {
			return position.z;
		}

		const Vec3& getPosition(void) {
			return position;
		}

		void addX(const Scalar& x) {
			position.x += x;
		}

		void addY(const Scalar& y) {
			position.y += y;
		}

		void addZ(const Scalar& z) {
			position.z += z;
		}

		static Factory<Component,ComponentPosition> compFactory;


};	// class ComponentPosition



#endif