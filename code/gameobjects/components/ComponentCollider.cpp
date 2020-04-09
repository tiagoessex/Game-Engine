

#include "ComponentCollider.h"
#include "../GameObject.h"
#include "../../physics/BulletPhysicsMgr.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::PhysicsSystem;


Factory<Component,ComponentCollider> ComponentCollider::compFactory;


ComponentCollider::ComponentCollider(void) :  
							Component("collider"),
							shape(0)
					
{}


ComponentCollider::~ComponentCollider(void) {}


void ComponentCollider::start() 
{
	PARAMETERSMAP::iterator it1 = owner->parameters.find("collidershape");
	if (it1 == owner->parameters.end()) { return; }
	shapetypeparam = (*it1).second;
	
	shapeID = BulletPhysicsMgr::getInstance()->getShapeID(shapetypeparam);
	if (shapeID != NONE) {
		shape = BulletPhysicsMgr::getInstance()->createShape(shapeID,owner->parameters);
	}
}


void ComponentCollider::end() 
{
	if (!shape) {
		return;
	}

	BulletPhysicsMgr::getInstance()->destroyShape(shape);	
}

