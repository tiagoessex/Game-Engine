
/**
		lifetime of a go since its creation (insertion in a system)

	PARAMETERS:
		- [lifespan]	- max life
		
*/


#ifndef __ComponentLifeSpan_H__
#define __ComponentLifeSpan_H__

#include "Component.h"
#include "../../Prerequisites.h"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class ComponentLifeSpan;
	}
}


class Venator::GameObjectComponentSystem::ComponentLifeSpan : public Component {

	public:
		Scalar current_life;
		Scalar lifespan;

	public:
		ComponentLifeSpan(void);
		~ComponentLifeSpan(void);
		
		void start();

		void setLifeSpan(const Scalar& l) { lifespan = l; }
		void setCurrentLifeSpan(const Scalar& l) { current_life = l; }
		const Scalar& getLifeSpan(void) { return lifespan; };
		const Scalar& getCurrentSpan(void) { return current_life; };
		

		static Factory<Component,ComponentLifeSpan> compFactory;

};	// class ComponentSpeed



#endif
