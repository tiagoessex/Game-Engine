

#include "CollisionsSystem.h"
#include "../GameObject.h"
#include "../../Globals.h"


#include "../../physics/BulletPhysicsMgr.h"
#include "../../events/EventsDispatcher.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::PhysicsSystem;


CollisionsSystem::CollisionsSystem(void) : BaseSystem("CollisionsSystem",true)//, 0.2f)
{
	LOGTORS("************ CollisionsSystem CTOR ************");	
}
	
CollisionsSystem::~CollisionsSystem(void) {
	LOGTORS("************ CollisionsSystem DTOR ************");
}


void CollisionsSystem::enter() {
	LOGINFO("[CollisionsSystem::enter] CollisionsSystem enter");	
	handleComponent("collisions");
	handleComponent("rigidbody");

	phyworld = BulletPhysicsMgr::getInstance()->getPhyWorld();
}

void CollisionsSystem::update(const std::vector<GameObject*>& gos) {

	int numManifolds = phyworld->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++) {
		btPersistentManifold* contactManifold =  phyworld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
		
		GameObject* o1 = static_cast<GameObject*> (obA->getUserPointer());
		GameObject* o2 = static_cast<GameObject*> (obB->getUserPointer());

		Venator::Events::HitInfo info;
		info.object1 = o1;
		info.object2 = o2;
		Venator::Events::EventsDispatcher::getInstance()->emitEvent(Venator::Events::COLLISIONHIT, &info);
	}
}

void CollisionsSystem::exit() {
	LOGINFO("[CollisionsSystem::exit] CollisionSystem exit");
}

/*		std::string tag1 = World::getInstance()->getTag(o1);  
		std::string tag2 = World::getInstance()->getTag(o2);
		LOGINFO(("COLLSIION between > " + tag1 + " + " + tag2).c_str());*/
