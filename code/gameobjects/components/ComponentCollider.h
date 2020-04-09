
/**

	PARAMETERS:
		- [collidershape]		- string

	
*/


#ifndef __ComponentCollider_H__
#define __ComponentCollider_H__

#include "Component.h"
#include "../../physics/BulletPhysicsCommon.h"


class btCollisionShape;


namespace Venator {	
	namespace GameObjectComponentSystem	{
		class ComponentCollider;
	}
}

class Venator::GameObjectComponentSystem::ComponentCollider : public Component {
		
			

	private:
		btCollisionShape* shape;
		Venator::PhysicsSystem::SHAPES shapeID;
		std::string shapetypeparam;	
		
	public:
		ComponentCollider(void);
		~ComponentCollider(void);			

		void start();
		void end();
		
		Venator::PhysicsSystem::SHAPES getShapeID(void) { return shapeID; };

		const std::string& getShapeName(void) { return shapetypeparam; }
		void setShapeName(const std::string& file) { shapetypeparam = file; }

		void setShape(btCollisionShape* s) { shape = s; }
		btCollisionShape* getShape(void) { return shape; }

		static Factory<Component,ComponentCollider> compFactory;

};



#endif