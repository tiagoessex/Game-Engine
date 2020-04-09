

#include "MotionStateSystem.h"
#include "../GameObject.h"
#include "../components/ComponentPosition.h"
#include "../components/ComponentRigidBody.h"

#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"
#include "../../Prerequisites.h"
#include "../../physics/BulletPhysicsMgr.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::PhysicsSystem;


MotionStateSystem::MotionStateSystem(void) : BaseSystem("MotionStateSystem")
{
	LOGTORS("************ MotionStateSystem CTOR ************");	
}
	
MotionStateSystem::~MotionStateSystem(void) {
	LOGTORS("************ MotionStateSystem DTOR ************");
}


void MotionStateSystem::enter() {
	LOGINFO("[MotionStateSystem::enter] MotionStateSystem enter");	
	handleComponent("position");	
//	handleComponent("speed");	
	handleComponent("rigidbody");
}

void MotionStateSystem::update(GameObject* go) {
	ComponentRigidBody* body = 0;
	body = static_cast<ComponentRigidBody*> (go->getComponent(RIGIDBODY));
	ComponentPosition* pos = 0;
	pos = static_cast<ComponentPosition*> (go->getComponent(POSITION));

	if (body->getRigidBody()) {
		POTransform temp;
		PhysicsSystem::BulletPhysicsMgr::getInstance()->getTransform(body->getRigidBody(), temp);	
		temp.position = pos->position;
		PhysicsSystem::BulletPhysicsMgr::getInstance()->setTransform(body->getRigidBody(),temp);
	}
}

void MotionStateSystem::exit() {
	LOGINFO("[MotionStateSystem::exit] MotionStateSystem exit");
}
