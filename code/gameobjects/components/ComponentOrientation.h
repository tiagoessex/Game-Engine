
/**
		transforms: orientation
		
	PARAMETERS: 
		- [orientation]		- "w,x,y,z" axis	(default: 1,0,0,0)
		
*/


#ifndef __ComponentOrientation_H__
#define __ComponentOrientation_H__

#include "Component.h"
#include "../../Prerequisites.h"



namespace Venator {	
	namespace GameObjectComponentSystem {
		class ComponentOrientation;
	}
}
class Venator::GameObjectComponentSystem::ComponentOrientation : public Component {

	public:				
		Quat orientation;	// public to inc performance

	public:
		ComponentOrientation(void) :  
							Component("orientation"),
							orientation(Quat::IDENTITY)	
		{};

		~ComponentOrientation(void)	{};

		void start(void);

		void setRW(const Scalar& w)	{
			orientation.w = w;
		}

		void setRX(const Scalar& x)	{
			orientation.x = x;
		}

		void setRY(const Scalar& y)	{
			orientation.y = y;
		}


		void setRZ(const Scalar& z)	{
			orientation.z = z;
		}

		
		void setOrientation(const Scalar& w, const Scalar& x, const Scalar& y, const Scalar& z)	{
			orientation.w = w;
			orientation.x = x;
			orientation.y = y;
			orientation.z = z;
		}

		void setOrientation(const Quat& r)	{
			orientation = r;
		}

		const Scalar& getRW(void) {
			return orientation.w;
		}

		const Scalar& getRX(void) {
			return orientation.x;
		}

		const Scalar& getRY(void) {
			return orientation.y;
		}

		const Scalar& getRZ(void) {
			return orientation.z;
		}

		const Quat& getOrientation(void) {
			return orientation;
		}


		static Factory<Component,ComponentOrientation> compFactory;

};



#endif