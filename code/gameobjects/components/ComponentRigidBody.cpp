

#include "ComponentRigidBody.h"
#include "../GameObject.h"
#include "../../utils/VenatorUtils.h"
#include "../../physics/BulletPhysicsMgr.h"
#include "ComponentCollider.h"

#include "ComponentPosition.h"
#include "ComponentOrientation.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::PhysicsSystem;

Factory<Component,ComponentRigidBody> ComponentRigidBody::compFactory;


ComponentRigidBody::ComponentRigidBody(void) :  
							Component("rigidbody"),
							rigidbody(0)
					
{}


ComponentRigidBody::~ComponentRigidBody(void) 
{}

void ComponentRigidBody::start() 
{
	POTransform transform;
	short group = -1;
	short mask = -1;


	ComponentPosition* pos = static_cast<ComponentPosition*>(owner->getComponent(POSITION));
	if (pos) {
		transform.position = pos->getPosition();
	}


	ComponentOrientation* ori = static_cast<ComponentOrientation*>(owner->getComponent(ORIENTATION));
	if (ori) {
		transform.orientation = ori->getOrientation();
	}

	ComponentCollider* c_collider = static_cast<ComponentCollider*> (getOwner()->getComponent(COLLIDER));
	if (!c_collider) { return; }
	
	btCollisionShape* shape = c_collider->getShape();		
	if (!shape) { return; }


	PARAMETERSMAP::iterator it = owner->parameters.find("colgroup");
	if (it != owner->parameters.end()) {
		group = Utils::String2Number<short>((*it).second);		
	}
	it = owner->parameters.find("colmask");
	if (it != owner->parameters.end()) {
		mask = Utils::String2Number<short>((*it).second);		
	}

	it = owner->parameters.find("kinematic");
	if (it != owner->parameters.end()) {
		if ((*it).second == "true") {
			if (group < 0 && mask < 0) {
				rigidbody = BulletPhysicsMgr::getInstance()->createKinematicRigidBody(shape,transform, (void*) (getOwner()));
			} else {
				rigidbody = BulletPhysicsMgr::getInstance()->createKinematicRigidBody(shape,transform, group, mask, (void*) (getOwner()));
			}
		}
	}

	// not kinematic => dynamic | static [+ mass]
	if (!rigidbody) {
		Scalar mass = 0;
		it = owner->parameters.find("mass");
		if (it != owner->parameters.end()) {
			 mass = Utils::String2Number<Scalar>((*it).second);
		}
		if (group < 0 && mask < 0) {
			rigidbody = BulletPhysicsMgr::getInstance()->createRigidBody(shape,mass,transform, (void*) (getOwner()));
		} else {
			rigidbody = BulletPhysicsMgr::getInstance()->createRigidBody(shape,mass,transform, group, mask, (void*) (getOwner()));
		}
	}
	
}


void ComponentRigidBody::end() 
{
	if (!rigidbody) {
		return;
	}

	BulletPhysicsMgr::getInstance()->destroyRigidBody(rigidbody);	
}

