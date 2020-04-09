
/**

	PARAMETERS:
		[kinematic] (optional) -- default: false
		[mass]		(optional) -- default: false
		[colgroup]	(optional)
		[colmask]	(optional)
		********* MASKS / GROUPS **********

	DEPDENCIES:
		- ComponentCollider	
		- ComponentPosition		- (optional)
		- ComponentOrientation	- (optional)

	NOTES:
		- userpointer: owner*
		- set mass parameter otherwise it will make it static
	
*/


#ifndef __ComponentRigidBody_H__
#define __ComponentRigidBody_H__

#include "Component.h"

class btRigidBody;

namespace Venator {	
	namespace GameObjectComponentSystem	{
		class ComponentRigidBody;
	}
}

class Venator::GameObjectComponentSystem::ComponentRigidBody : public Component {

	public:
		btRigidBody* rigidbody;
		
	public:
		ComponentRigidBody(void);
		~ComponentRigidBody(void);			

		void start();
		void end();
	
		void setRigidBody(btRigidBody* r) { rigidbody = r; }
		btRigidBody* getRigidBody(void) { return rigidbody; }

		static Factory<Component,ComponentRigidBody> compFactory;

};	// class ComponentEntity



#endif