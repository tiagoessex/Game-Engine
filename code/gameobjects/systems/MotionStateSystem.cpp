

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
	handleComponent("rigidbody");
}

void MotionStateSystem::update(GameObject* go) {
	ComponentRigidBody* body = 0;
	body = static_cast<ComponentRigidBody*> (go->getComponent(RIGIDBODY));	
	btRigidBody* rgbody = body->getRigidBody();
	if (body) {
		// update kinematic objs => go transform -> physics transform
		if (rgbody->isKinematicObject()) {
			ComponentPosition* pos = 0;
			pos = static_cast<ComponentPosition*> (go->getComponent(POSITION));
			POTransform temp;
			PhysicsSystem::BulletPhysicsMgr::getInstance()->getTransform(rgbody, temp);	
			temp.position = pos->position;
			PhysicsSystem::BulletPhysicsMgr::getInstance()->setTransform(rgbody,temp);			
		// udpate dynamic objs => physics transform -> go transform
		} else if (rgbody->getInvMass() != 0) {
			ComponentPosition* pos = 0;
			pos = static_cast<ComponentPosition*> (go->getComponent(POSITION));
			POTransform temp;
			PhysicsSystem::BulletPhysicsMgr::getInstance()->getTransform(rgbody, temp);	
			pos->position = temp.position;				
		}
	}
}

void MotionStateSystem::exit() {
	LOGINFO("[MotionStateSystem::exit] MotionStateSystem exit");
}
