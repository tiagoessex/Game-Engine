

/**
	
	on collision emit signal:
			sigc::signal<void, btCollisionObject*, btCollisionObject*> collision;

	connected to:
			Venator::Actions::onCollision

	ex:
	
		int COL_NOTHING = 0;
		int COL_SHIP = 1<<0;
		int COL_WALL = 1<<1;
		int COL_POWERUP = 1<<2;
		int shipCollidesWith = COL_POWERUP;
		int wallCollidesWith = COL_NOTHING;	//COL_POWERUP;//COL_NOTHING;
		int powerupCollidesWith = COL_SHIP | COL_WALL;

		PhysicsSystem::BulletPhysicsMgr::getInstance()->initialise(1/180.f, 10, 1/60.f);	
		PhysicsSystem::BulletPhysicsMgr::getInstance()->setDebugDraw(RenderEngine::getSingletonPtr()->getSceneManager());			
		PhysicsSystem::BulletPhysicsMgr::getInstance()->setGravity(Vec3(0,-10,0));

		btCollisionShape* shape1 = PhysicsSystem::BulletPhysicsMgr::getInstance()->boxShape(Vec3(5,5,5));
		POTransform t1;
		t1.orientation = Quat(Quat::IDENTITY);
		t1.position = Vec3(0,5,0);
		body = PhysicsSystem::BulletPhysicsMgr::getInstance()->createKinematicRigidBody(shape1,t1,COL_SHIP,shipCollidesWith);


		btCollisionShape* shape2 = PhysicsSystem::BulletPhysicsMgr::getInstance()->coneShape(5,10);
		POTransform t2;
		t2.orientation = Quat(Quat::IDENTITY);
		t2.position = Vec3(0,100,0);
		btRigidBody* b = PhysicsSystem::BulletPhysicsMgr::getInstance()->createRigidBody(shape2,1.0,t2,COL_POWERUP,powerupCollidesWith);
	
	
		btCollisionShape* shape3 = PhysicsSystem::BulletPhysicsMgr::getInstance()->planeShape(10,10);//infinitePlaneShape(Vec3(0,1,0),0);
		POTransform t3;
		t3.orientation = Quat(Quat::IDENTITY);
		t3.position = Vec3(0,-5,0);
		PhysicsSystem::BulletPhysicsMgr::getInstance()->createRigidBody(shape3,0,t3,COL_WALL,wallCollidesWith);
	
		btCollisionShape* shape4 = PhysicsSystem::BulletPhysicsMgr::getInstance()->sphereShape(10);
		POTransform t4;
		t4.orientation = Quat(Quat::IDENTITY);
		t4.position = Vec3(15,0,0);
		ghost = PhysicsSystem::BulletPhysicsMgr::getInstance()->createGhost(shape4,t4);
		btGhostObject* ghost2 = PhysicsSystem::BulletPhysicsMgr::getInstance()->createGhost(shape4,t4);
	

	transforms:
			btTransform qwe;
			body->getMotionState()->getWorldTransform(qwe);
			btVector3 c = qwe.getOrigin();
			c.setX(c.getX() - 5);
			qwe.setOrigin(c);
			body->getMotionState()->setWorldTransform(qwe);

		or:
			// not very efficient - need to change transforms
			POTransform temp;
			PhysicsSystem::BulletPhysicsMgr::getInstance()->getTransform(body, temp);
			temp.position.x = temp.position.x + 5;
			PhysicsSystem::BulletPhysicsMgr::getInstance()->setTransform(body,temp);

	ghost object:
			... create ghost ...
			// in loop check for collisions with the ghost
			if (ghost->getNumOverlappingObjects()>0) {
				for (int i=0; i<ghost->getNumOverlappingObjects();++i) {
			//	btCollisionObject* obj = ghost->getOverlappingObject(i);
			//	btRigidBody* body1 = btRigidBody::upcast(obj);
			//	Ogre::SceneNode* node2 = static_cast<Ogre::SceneNode*>(body1->getUserPointer());
					LOGINFO(("CONTACT WITH GHOST").c_str());
				}
			}
	
	raycast:
			btCollisionWorld::ClosestRayResultCallback RayCallback(btVector3(-100,1,0), btVector3(100,1,0));
			PhysicsSystem::BulletPhysicsMgr::getInstance()->getPhyWorld()->rayTest(btVector3(-100,1,0), btVector3(100,1,0), RayCallback);
			if(RayCallback.hasHit()) {
				LOGINFO("RAY 2 HIT");
			}


	get contacts of a body:
		btAlignedObjectArray<btCollisionObject*> col = PhysicsSystem::BulletPhysicsMgr::getInstance()->getCollisionsWith(body);
		if ((col.size() > 0)) {
			LOGINFO(("BODY CONTACT WITH " + Number2String(col.size())).c_str());
			col.resize(0);
		}
*/



#ifndef __BulletPhysicsMgr_h_
#define __BulletPhysicsMgr_h_


#include "../Prerequisites.h"
#include "BulletDebugDrawer.h"
#include "BulletPhysicsPrerequisites.h"
#include "../Globals.h"
#include "BulletPhysicsCommon.h"

#include <btBulletDynamicsCommon.h>

#include <string>
#include <map>

//#include "sigc++/sigc++.h"


namespace Venator {
	class MeshStrider;

	namespace PhysicsSystem	{
		class BulletPhysicsMgr;
	}
}

class btGhostObject;
class btGhostPairCallback;

class Venator::PhysicsSystem::BulletPhysicsMgr
{
	public:	

		// ****************
		// **** SETUP  ****
		// ****************
		bool initialise(const btScalar& time_step, int n_sub_steps, const btScalar& fixed );
		void destroy(void);
		void reset(void);
		
		void destroyRigidBody(btRigidBody* body);
		void destroyShape(btCollisionShape* shape);

		void updateStart(void);	
		void update(const Scalar& step);
		void updateEnd(void);

		void setGravity(const Vec3& vec);

		void addShape(btCollisionShape* sh);
		void addRigidBody(btRigidBody* body);

		btDiscreteDynamicsWorld* getPhyWorld(void) { return dynamicsWorld; }

		void setDebugDraw(Ogre::SceneManager* scenemanager);

		
		// ****************
		// **** SHAPES ****
		// ****************

		/**
			create an infitite collision place and added it to the shape collection
			@param const Vec3&
				normal vector giving plane orientation
			@param const Scalar&
				double indicating the offset between origin (0,0,0) and the plane
		*/
		btCollisionShape* infinitePlaneShape(const Vec3& normal, const Scalar& distance_from_origin);

		/**
			create an box collision shape and added it to the shape collection
			@param const Vec3&
				box dimension  specified by half extents, in local shape coordinates
				this means that (2,2,2) is really 1 unit for each side of the center of the local cs
		*/
		btCollisionShape* boxShape(const Vec3& dimensions);
		
		/**
			create an sphere collision shape and added it to the shape collection
			@param const Scalar&
				sphere radius
		*/
		btCollisionShape* sphereShape(const Scalar& radius);

		/**
			create an cylinder collision shape and added it to the shape collection
			@param const Vec3&
				box dimension centered to the cs center
		*/
		btCollisionShape* cylinderShape(const Vec3 &limits);

		/**

		*/
		btCollisionShape* coneShape(const Scalar &radius, const Scalar &height);

		/**

		*/
		btCollisionShape* capsuleShape(const Scalar &radius, const Scalar &height);


		/**
			create an plane collision shape centered to the origin and added it to the shape collection
			this plane is just 2 triangles (bttrianglemesh)
			center square ((0,0),(x,y))
			@param const Scalar
				 right x corner
			@param const Scalar
				 right y corner
		*/
		btCollisionShape* planeShape(const Scalar &x, const Scalar &y);


		/**
			create an complex collision shape based on a mesh and added it to the shape collection
			@param const std::string&
				mesh for reference
			@param std::string& gp
				resource group
			ex:
				PhyShape * CollisionShape = BulletPhysicsMgr::getSingletonPtr()->meshShape("ogrehead.mesh","Popular");
				ogrebody = BulletPhysicsMgr::getSingletonPtr()->createRigidBody(CollisionShape, 0.0f, PhyTransform(PhyQuat(0,0,0,1),PhyVec3(0,5,-20)));
		*/
		btCollisionShape* meshShape(const std::string& mesh, const std::string& gp);

		/**
			create an convex collision shape based on a mesh and added it to the shape collection
			@param const std::string&
				mesh for reference	
			@param bool
				if true, it will create an optmized version of the shape (less vertexes)
			ex:
				Ogre::Entity* complex = RenderEngine::getSingletonPtr()->getSceneManager()->createEntity("ogre", "ogrehead.mesh");
				PhyShape * CollisionShape =  BulletPhysicsMgr::getSingletonPtr()->convexMeshShape(&complex->getMesh(), false);
				ogrebody = BulletPhysicsMgr::getSingletonPtr()->createRigidBody(CollisionShape, 0.0f, PhyTransform(PhyQuat(0,0,0,1),PhyVec3(0,5,-20)));
			*/
		btCollisionShape* convexMeshShape(const Ogre::MeshPtr* const mesh, bool optimize = true);
		
		/**
			create shape from shapeID and parameters given by a map
		*/
		btCollisionShape* createShape(SHAPES shape, std::map<std::string, std::string>& parameters);

		// ****************
		// **** BODIES ****
		// ****************
		/**
			create a dynamic rigid body + motion state + add it to the world
		*/
		btRigidBody* createRigidBody(btCollisionShape* shape, float mass, const POTransform& transform, void* userdata = 0);
		btRigidBody* createRigidBody(btCollisionShape* shape, float mass, const POTransform& transform, short group, short mask, void* userdata = 0);

		/**
			create a kinematic rigid body + motion state + add it to the world
		*/
		btRigidBody* createKinematicRigidBody(btCollisionShape* shape, const POTransform& transform, void* userdata = 0);
		btRigidBody* createKinematicRigidBody(btCollisionShape* shape, const POTransform& transform, short group, short mask, void* userdata = 0);

		// *****************************
		// **** GHOSTS AND TRIGGERS ****
		// *****************************

		/**
			set body as trigger
			=> trepassable + collision detection
		*/
		void setAsTrigger(btRigidBody* body);

		/**
			ghost object
			=> no rigid body + trepassable + collision detection

			to get collision with the ghost:
				if (ghost->getNumOverlappingObjects()>0) {
					for (int i=0; i<ghost->getNumOverlappingObjects();++i) {
						btCollisionObject* obj = ghost->getOverlappingObject(i);
						btRigidBody* body1 = btRigidBody::upcast(obj);
						...
						LOGINFO(("GHOST CONTACT" + Number2String(n)).c_str());
					}
				}
		*/
		btGhostObject* createGhost(btCollisionShape* shape, const POTransform& transform, void* userdata = 0);
		btGhostObject* createGhost(btCollisionShape* shape, const POTransform& transform, short group, short mask, void* userdata = 0);


		// ********************
		// **** TRANSFORMS ****
		// ********************

		void getTransform(btCollisionObject* obj, POTransform& transform);
		void setTransform(btCollisionObject* obj, const POTransform& newtransform);

		// ********************
		// **** COLLISIONS ****
		// ********************

		btAlignedObjectArray<btCollisionObject*> getCollisionsWith(btCollisionObject* obj);

		// ****************
		// **** XXXXX  ****
		// ****************

		const std::string& getShapeName(SHAPES shape);
		SHAPES getShapeID(const std::string& shapename);

		static BulletPhysicsMgr* getInstance(void);
		static BulletPhysicsMgr& getSingleton(void);		
	private:
		BulletPhysicsMgr(void);		
		virtual ~BulletPhysicsMgr(void);
		BulletPhysicsMgr( const BulletPhysicsMgr& ) { }
		BulletPhysicsMgr & operator = ( const BulletPhysicsMgr& );
		
		void _destroyAllBodies(void);
		void _destroyAllShapes(void);
		btRigidBody* _createRigidBody(btCollisionShape* shape, float mass, const POTransform& transform, void* userdata);
		btGhostObject* _createGhost(btCollisionShape* shape, const POTransform& transform, void* userdata);

		btBroadphaseInterface* broadphase;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
		btGhostPairCallback* ghostcallback;

		btScalar time_step;
		int n_sub_steps;
		btScalar fixed;


		OgreDebugDrawer* debugdrawer;		
		
		btAlignedObjectArray<btCollisionShape*> shapes_collection;

		static BulletPhysicsMgr *mBulletPhysicsMgr;

		std::map<SHAPES, std::string> shapesnames;

		//sigc::signal<void, btCollisionObject*, btCollisionObject*> collision;
		//sigc::connection c;

};


#endif
