
/**
		speed component 

	PARAMETERS:
		- [max_front_speed]
		- [rotation_speed]
		- [initial_speed]

*/


#ifndef __ComponentSpeed_H__
#define __ComponentSpeed_H__

#include "Component.h"
#include "../../Prerequisites.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class ComponentSpeed;
	}
}


class Venator::GameObjectComponentSystem::ComponentSpeed : public Component {

	public:
		ComponentSpeed(void);
		~ComponentSpeed(void);
		
		void start();		

		void setSpeed(const Scalar& s) { current_speed = s; };
		const Scalar& getSpeed(void) { return current_speed; };

		Scalar max_front_speed;
		Scalar rotation_speed;
		Scalar current_speed;


		static Factory<Component,ComponentSpeed> compFactory;

};



#endif
