


// venator headers
#include "../Globals.h"
#include "../utils/VenatorUtils.h"
//#include "RenderEngine.h"
#include "BulletPhysicsMgr.h"
#include "MeshStrider.h"					// for mesh based shapes
#include "MeshInfo.h"						// for convex hull shapes


// ogre headers
#include <OgreMeshManager.h>


// bullet headers
#include "C:/programming/bullet-2.79/src/BulletCollision/CollisionShapes/btShapeHull.h"
// if ghost objects are used, uncomment this line
#include "C:/programming/bullet-2.79/src/BulletCollision/CollisionDispatch/btGhostObject.h"//



using namespace Venator;
using namespace Venator::PhysicsSystem;


BulletPhysicsMgr *BulletPhysicsMgr::mBulletPhysicsMgr = 0;

BulletPhysicsMgr::BulletPhysicsMgr(void) :  
				debugdrawer(0),
				broadphase(0),
				collisionConfiguration(0),
				dispatcher(0),
				solver(0),
				dynamicsWorld(0),
				ghostcallback(0)

{}

BulletPhysicsMgr::~BulletPhysicsMgr(void) 
{}

// ****************
// **** SETUP  ****
// ****************


bool BulletPhysicsMgr::initialise(const btScalar& time_step, int n_sub_steps, const btScalar& fixed) 
{
	this->time_step		= time_step;
	this->n_sub_steps	= n_sub_steps;
	this->fixed			= fixed;

	// Build the broadphase
	broadphase = new btDbvtBroadphase(); 
	// Set up the collision configuration and dispatcher
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration); 
	// The actual physics solver
	solver = new btSequentialImpulseConstraintSolver;
	// The world
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
	
	// for ghost 
	ghostcallback = new btGhostPairCallback();
	broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(ghostcallback);

	// in case personal callback
	//gContactProcessedCallback = _myContactProcessedCallback;
	
//	c = collision.connect( sigc::ptr_fun(Venator::Actions::onCollision) );

	shapesnames[CUBE]			= "cube";
	shapesnames[SPHERE]			= "sphere";
	shapesnames[PLANE]			= "plane";
	shapesnames[INFINITEPLANE]	= "infplane";
	shapesnames[CYLINDER]		= "cylinder";
	shapesnames[CONE]			= "cone";
	shapesnames[CAPSULE]		= "capsule";
	shapesnames[MESH]			= "mesh";
	shapesnames[CONVEX]			= "convex";
	shapesnames[COMPOUND]		= "compound";
	shapesnames[NONE]			= "none";

	return true;
}


void BulletPhysicsMgr::destroy(void) 
{
	reset();

    if (dynamicsWorld)			{ delete dynamicsWorld; }
    if (solver)					{ delete solver; }
    if (dispatcher)				{ delete dispatcher; }
    if (collisionConfiguration) { delete collisionConfiguration; }
    if (broadphase)				{ delete broadphase; }
	if (ghostcallback)			{ delete ghostcallback; }
	if (debugdrawer)			{ delete debugdrawer; }

	if ( getInstance() )		{ delete mBulletPhysicsMgr; }
}

void BulletPhysicsMgr::reset(void) 
{	
	_destroyAllBodies();
	_destroyAllShapes();
	shapesnames.clear();
}


void BulletPhysicsMgr::setDebugDraw(Ogre::SceneManager* scenemanager) 
{ 
	if (!debugdrawer) {
		debugdrawer = new  OgreDebugDrawer(scenemanager,2.0f);
		debugdrawer->setDebugMode(	btIDebugDraw::DBG_DrawWireframe |
								btIDebugDraw::DBG_DrawContactPoints);
		dynamicsWorld->setDebugDrawer(debugdrawer);
	}
};


void BulletPhysicsMgr::_destroyAllBodies(void) 
{
	LOGINFO(("eliminating [" + Utils::Number2String(dynamicsWorld->getNumCollisionObjects()) + "] rigid bodies").c_str());
	for (int i = dynamicsWorld->getNumCollisionObjects()-1; i>=0; i--) {
		btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState()) {
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}
	LOGINFO(("rigid bodies after elimination [" + Utils::Number2String(dynamicsWorld->getNumCollisionObjects()) + "]").c_str());
}


void BulletPhysicsMgr::_destroyAllShapes(void) 
{

	LOGINFO(("eliminating [" + Utils::Number2String(shapes_collection.size()) + "] shapes").c_str());

	for (int i=0; i<shapes_collection.size();i++) {
		btCollisionShape* shape = shapes_collection[i];		
		if (0 != shape->getUserPointer()) {
			std::string name = std::string(shape->getName());

			// is e.g. a btTriangleMesh was used to create the shape then 
			// it also must be cleared
			if ( name == "BVHTRIANGLEMESH")	{
				delete static_cast<btStridingMeshInterface*>(shape->getUserPointer());
				shape->setUserPointer(0);
			}
		}
		delete shape;
	}
	shapes_collection.clear();

	LOGINFO(("shapes after elimination  [" + Utils::Number2String(shapes_collection.size()) + "]").c_str());
}


void BulletPhysicsMgr::destroyRigidBody(btRigidBody* body)
{
	if (body->getMotionState())
		delete body->getMotionState();
	dynamicsWorld->removeCollisionObject(body);
	delete body;
}



void BulletPhysicsMgr::destroyShape(btCollisionShape* shape) 
{
	for (int i=0; i<shapes_collection.size();i++) {		
		if (shapes_collection[i] == shape) {
			btCollisionShape* _shape = shapes_collection[i];
						
			if (0 != shape->getUserPointer()) {
				std::string name = std::string(shape->getName());
				if ( name == "BVHTRIANGLEMESH")	{
					delete static_cast<btStridingMeshInterface*>(shape->getUserPointer());
					shape->setUserPointer(0);
				}
			}

			delete _shape;
			shapes_collection.remove(_shape);			
			return;
		}		
	}
}



void BulletPhysicsMgr::updateStart(void) 
{

	if (debugdrawer) {
		dynamicsWorld->debugDrawWorld();
		debugdrawer->updateStart();
	}
}


void BulletPhysicsMgr::update(const Scalar& step) 
{
	dynamicsWorld->stepSimulation(time_step, n_sub_steps, fixed); 

/*	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++) {
		btPersistentManifold* contactManifold =  dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
		collision.emit(obA, obB);
	}*/
}

void BulletPhysicsMgr::updateEnd(void)
{
	if (debugdrawer) {	
		debugdrawer->updateEnd();
	}
}



void BulletPhysicsMgr::setGravity(const Vec3& vec) 
{
	dynamicsWorld->setGravity(Vec3Physics(vec));
}

void BulletPhysicsMgr::addShape(btCollisionShape* sh) 
{
	shapes_collection.push_back(sh);
}

void BulletPhysicsMgr::addRigidBody(btRigidBody* body) 
{
	dynamicsWorld->addRigidBody(body);
}

// ****************
// **** SHAPES ****
// ****************


btCollisionShape* BulletPhysicsMgr::infinitePlaneShape(const Vec3& normal, const Scalar& distance_from_origin) 
{
	btCollisionShape* shape = new btStaticPlaneShape(Vec3Physics(normal),distance_from_origin);	
	shapes_collection.push_back(shape);
	return shape;
}



btCollisionShape* BulletPhysicsMgr::boxShape(const Vec3& dimensions) 
{
	btCollisionShape* shape = new btBoxShape(Vec3Physics(dimensions));
	shapes_collection.push_back(shape);
	return shape;
}


btCollisionShape* BulletPhysicsMgr::sphereShape(const Scalar& radius)
{
	btCollisionShape* shape = new btSphereShape(radius);	
	shapes_collection.push_back(shape);
	return shape;
}

btCollisionShape* BulletPhysicsMgr::cylinderShape(const Vec3 &limits)
{
	btCollisionShape* shape = new btCylinderShape(Vec3Physics(limits));
	shapes_collection.push_back(shape);
	return shape;
}


btCollisionShape* BulletPhysicsMgr::coneShape(const Scalar &radius, const Scalar &height) 
{
	btCollisionShape* shape = new btConeShape(radius,height);
	shapes_collection.push_back(shape);
	return shape;
}



btCollisionShape* BulletPhysicsMgr::capsuleShape(const Scalar &radius, const Scalar &height) 
{
	btCollisionShape* shape = new btCapsuleShape(radius,height);
	shapes_collection.push_back(shape);
	return shape;
}


btCollisionShape* BulletPhysicsMgr::planeShape(const Scalar &x, const Scalar &y)
{
	btTriangleMesh* mTriMesh1 = new btTriangleMesh();
	btVector3 v0(-x/2,0,-y/2);
	btVector3 v1(x/2,0,-y/2);
	btVector3 v2(-x/2,0,y/2);
	mTriMesh1->addTriangle(v0,v1,v2);

	btVector3 v4(x/2,0,y/2);
	btVector3 v5(-x/2,0,y/2);
	mTriMesh1->addTriangle(v1,v4,v5);

	btCollisionShape *shape = new btBvhTriangleMeshShape(mTriMesh1,true);	
	shape->setUserPointer((btStridingMeshInterface *) mTriMesh1);

	shapes_collection.push_back(shape);

	return shape;
}





btCollisionShape* BulletPhysicsMgr::meshShape(const std::string& mesh, const std::string& gp)
{
	Ogre::MeshPtr MeshPtr = Ogre::Singleton<Ogre::MeshManager>::getSingletonPtr()->load(mesh, gp);
	MeshStrider* Strider = new MeshStrider(MeshPtr.get());
	btCollisionShape* shape = new btBvhTriangleMeshShape(Strider,true,true);

	shape->setUserPointer((btStridingMeshInterface *) Strider);

	shapes_collection.push_back(shape);	
	return shape;
}

btCollisionShape* BulletPhysicsMgr::convexMeshShape(const Ogre::MeshPtr* const mesh, bool optimize) 
{
	size_t vertex_count,index_count;
	Ogre::Vector3* vertices;
	unsigned long* indices;
	Ogre::Vector3 pos, ori, sca;
	Ogre::Vector3 position = Ogre::Vector3::ZERO;
	Ogre::Quaternion orient = Ogre::Quaternion::IDENTITY;
	Ogre::Vector3 scale = Ogre::Vector3::UNIT_SCALE;


	getMeshInformation(mesh,vertex_count,vertices,index_count,indices, position, orient, scale);
	btCollisionShape * CollisionShape = new btConvexHullShape();
	for ( unsigned int ii=0; ii<vertex_count; ++ii )
		static_cast<btConvexHullShape*>(CollisionShape)->addPoint( Vec3Physics(vertices[ii]) );
		

	delete[] vertices;
	delete[] indices;

	if (!optimize) {
		CollisionShape->setUserPointer(0);
		shapes_collection.push_back(CollisionShape);	
		return CollisionShape;
	}
		

	btShapeHull* hull = new btShapeHull(static_cast<btConvexHullShape*>(CollisionShape));
	btScalar margin = CollisionShape->getMargin();
	hull->buildHull(margin);

	btCollisionShape* convexShape = new btConvexHullShape();
	for ( int i=0; i<hull->numVertices(); i++ )	{
		static_cast<btConvexHullShape*>(convexShape)->addPoint(hull->getVertexPointer()[i]);	
	}

	delete CollisionShape;
	delete hull;

	convexShape->setUserPointer(0);
	shapes_collection.push_back(convexShape);	
	return convexShape;	
}


btCollisionShape* BulletPhysicsMgr::createShape(SHAPES shape, std::map<std::string, std::string>& parameters) 
{
	switch (shape) {
		case CUBE:
			return boxShape(Utils::String2Vec3(parameters["shape_box_dimensions"]));
			break;
		case SPHERE:
			return sphereShape(Utils::String2Number<Scalar>(parameters["shape_sphere_radius"]));
			break;
		case PLANE:
			return planeShape(Utils::String2Number<Scalar>(parameters["shape_plane_x"]),Utils::String2Number<Scalar>(parameters["shape_plane_y"]));
			break;	
		case INFINITEPLANE:			
			return infinitePlaneShape(Utils::String2Vec3(parameters["shape_infplane_normal"]), Utils::String2Number<Scalar>(parameters["shape_distance"]));
			break;
		case CYLINDER:
			return cylinderShape(Utils::String2Vec3(parameters["shape_cylinder_dimensions"]));
			break;
		case CONE:
			return coneShape(Utils::String2Number<Scalar>(parameters["shape_cone_radius"]),Utils::String2Number<Scalar>(parameters["shape_cone_height"]));
			break;
		case CAPSULE:
			return capsuleShape(Utils::String2Number<Scalar>(parameters["shape_capsule_radius"]),Utils::String2Number<Scalar>(parameters["shape_capsule_height"]));
			break;
		case MESH:
			return meshShape(parameters["mesh"], parameters["group"]);
			break;
	/*	case CONVEX:
			return convexMeshShape(const Ogre::MeshPtr* const mesh, bool optimize = true);
			break;*/
		case COMPOUND:
			break;
		default: break;
	}
	return 0;
}


// ****************
// **** BODIES ****
// ****************


btRigidBody* BulletPhysicsMgr::_createRigidBody(btCollisionShape* shape, float mass, const POTransform& transform, void* userdata) 
{
	btDefaultMotionState* motionState = new btDefaultMotionState(TransPhysics(transform));
	bool isDynamic = (mass != 0.f);
	btVector3 inertia(0,0,0);
	if (isDynamic) { shape->calculateLocalInertia(mass,inertia); }
	btRigidBody::btRigidBodyConstructionInfo rigidBody (mass,motionState,shape,inertia);
	btRigidBody* temp = new btRigidBody(rigidBody);
	temp->setUserPointer(userdata);
	return temp;
}

btRigidBody* BulletPhysicsMgr::createRigidBody(btCollisionShape* shape, float mass, const POTransform& transform, void* userdata) 
{
	btRigidBody* temp = _createRigidBody(shape, mass, transform, userdata );
	dynamicsWorld->addRigidBody(temp);
	return temp;
}


btRigidBody* BulletPhysicsMgr::createRigidBody(btCollisionShape* shape, float mass, const POTransform& transform,short group, short mask, void* userdata) 
{
	btRigidBody* temp = _createRigidBody(shape, mass, transform, userdata );
	dynamicsWorld->addRigidBody(temp, group, mask);
	return temp;
}

btRigidBody* BulletPhysicsMgr::createKinematicRigidBody(btCollisionShape* shape, const POTransform& transform, void* userdata) 
{
	btRigidBody* temp = _createRigidBody(shape, 0, transform, userdata );

	temp->setCollisionFlags(temp->getCollisionFlags() |  btCollisionObject::CF_KINEMATIC_OBJECT);
	temp->setActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(temp);	

	// activate collisions - no group && no mask
	btBroadphaseProxy *bproxy = temp->getBroadphaseHandle();
	if( bproxy ) {
		bproxy->m_collisionFilterGroup = short( btBroadphaseProxy::DefaultFilter );
		bproxy->m_collisionFilterMask = short( btBroadphaseProxy::AllFilter );
	} 

	return temp;
}


btRigidBody* BulletPhysicsMgr::createKinematicRigidBody(btCollisionShape* shape, const POTransform& transform,short group, short mask, void* userdata) 
{
	btRigidBody* temp = _createRigidBody(shape, 0, transform, userdata );

	temp->setCollisionFlags(temp->getCollisionFlags() |  btCollisionObject::CF_KINEMATIC_OBJECT);
	temp->setActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(temp, group, mask);	

	// activate collisions ??????????????
/*	btBroadphaseProxy *bproxy = temp->getBroadphaseHandle();
	if( bproxy ) {
		bproxy->m_collisionFilterGroup = short( btBroadphaseProxy::DefaultFilter );
		bproxy->m_collisionFilterMask = short( btBroadphaseProxy::AllFilter );
	} */

	return temp;
}

// *****************************
// **** GHOSTS AND TRIGGERS ****
// *****************************

void BulletPhysicsMgr::setAsTrigger(btRigidBody* body) 
{
	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

btGhostObject* BulletPhysicsMgr::_createGhost(btCollisionShape* shape, const POTransform& transform, void* userdata) 
{
	btGhostObject* ghostObject = new btGhostObject();
	ghostObject->setCollisionShape(shape);	
	ghostObject->setWorldTransform(TransPhysics(transform));
	ghostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	ghostObject->setUserPointer(userdata);
	return ghostObject;
}

btGhostObject* BulletPhysicsMgr::createGhost(btCollisionShape* shape, const POTransform& transform, void* userdata) 
{
	btGhostObject* ghostObject = _createGhost(shape,transform, userdata);
	dynamicsWorld->addCollisionObject(ghostObject);
	return ghostObject;
}


btGhostObject* BulletPhysicsMgr::createGhost(btCollisionShape* shape, const POTransform& transform, short group, short mask, void* userdata) 
{
	btGhostObject* ghostObject = _createGhost(shape,transform, userdata);
	dynamicsWorld->addCollisionObject(ghostObject, group, mask);
	return ghostObject;
}



// ********************
// **** TRANSFORMS ****
// ********************

void BulletPhysicsMgr::getTransform(btCollisionObject* obj, POTransform& transform) 
{
	btTransform temp;
	btRigidBody::upcast(obj)->getMotionState()->getWorldTransform(temp);
	transform = PhysicsTrans(temp);
	//return PhysicsTrans(temp);
}

void BulletPhysicsMgr::setTransform(btCollisionObject* obj, const POTransform& newtransform) 
{
	btRigidBody::upcast(obj)->getMotionState()->setWorldTransform(TransPhysics(newtransform));
}



// ********************
// **** COLLISIONS ****
// ********************

btAlignedObjectArray<btCollisionObject*> BulletPhysicsMgr::getCollisionsWith(btCollisionObject* obj) 
{
	
	btAlignedObjectArray<btCollisionObject*> collisions;

	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++) {
		btPersistentManifold* contactManifold =  dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
		
		if (obA == obj) {
			collisions.push_back(obB);
		} else if (obB == obj) {
			collisions.push_back(obA);
		}
	}
	return collisions;
}


// ****************
// **** XXXXX  ****
// ****************


const std::string& BulletPhysicsMgr::getShapeName(SHAPES shape) 
{
	return shapesnames[shape];
}

SHAPES BulletPhysicsMgr::getShapeID(const std::string& shapename) 
{
	std::map<SHAPES, std::string>::iterator it;// = shapesnames.find(shape);
	for (it = shapesnames.begin(); it != shapesnames.end(); it++) {
		if ((*it).second == shapename ) {
			return (*it).first;
		}
	}
	return NONE;	
}


BulletPhysicsMgr& BulletPhysicsMgr::getSingleton(void) 
{  
    assert(mBulletPhysicsMgr);
    return *mBulletPhysicsMgr;
}


BulletPhysicsMgr* BulletPhysicsMgr::getInstance( void ) 
{
	if( !mBulletPhysicsMgr ) {
        mBulletPhysicsMgr = new BulletPhysicsMgr();
    }
    return mBulletPhysicsMgr;
}