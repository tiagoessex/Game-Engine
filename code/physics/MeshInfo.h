/**


void getMeshInformation(Ogre::Entity* entity, //const Ogre::Mesh* const mesh,
                        size_t &vertex_count,
                        Ogre::Vector3* &vertices,
                        size_t &index_count,
                        unsigned long* &indices,
                        const Ogre::Vector3 &position,
                        const Ogre::Quaternion &orient,
                        const Ogre::Vector3 &scale);


*/



#ifndef _MeshInfo_h_
#define _MeshInfo_h_


#include "OgrePrerequisites.h"


namespace Ogre
{
	class Node;
	class Entity;
}




namespace Venator
{
	//Ogre::Entity* entity, //
	void getMeshInformation(const Ogre::MeshPtr* const mesh,
							size_t &vertex_count,
							Ogre::Vector3* &vertices,
							size_t &index_count,
							unsigned long* &indices,
							const Ogre::Vector3 &position,
							const Ogre::Quaternion &orient,
							const Ogre::Vector3 &scale);


}

#endif




/*

	GETTING MESH INFO - VERTEX + INDEXES	v1.0
  			

	notes: original taken from forum


	usage:

	entity:

		Ogre::Entity* ogre1 = mSceneMgr->createEntity("ogre1","ogrehead.mesh"); 
		Ogre::SceneNode* ogreNode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("ogre1");
		ogreNode1->attachObject(ogre1);
		ogreNode1->setPosition(0,0,0);
		ogreNode1->showBoundingBox(true);

	set to get info:
 
		size_t vertex_count,index_count;
		Ogre::Vector3* vertices;
		unsigned long* indices;
		Ogre::Vector3 pos, ori, sca;
		Ogre::Vector3 position = Ogre::Vector3::ZERO;
		Ogre::Quaternion orient = Ogre::Quaternion::IDENTITY;
		Ogre::Vector3 scale = Ogre::Vector3::UNIT_SCALE;

	get info:

		getMeshInformation(ogre1,vertex_count,vertices,index_count,indices, position, orient, scale);
 
	use info:
 
		Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL,"Vertices in mesh: %lu",vertex_count);
		Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL,"Triangles in mesh: %lu",index_count / 3);
 
		for (int i=0; i<vertex_count; i++)
		{
			Ogre::String str = "vertex " + Ogre::StringConverter().toString(i) + " > " + 
					Ogre::StringConverter().toString(vertices[i]);
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL,str);
		}

		for (int i=0; i<index_count; i++)
		{
			Ogre::String str = "index " + Ogre::StringConverter().toString(i) + " > " + 
					Ogre::StringConverter().toString(indices[i]);
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL,str);
		}

		delete[] vertices;
		delete[] indices;

	-------------------------
	example usagte for btConvexHullShape 


	Ogre::Entity* complex = RenderEngine::getSingletonPtr()->getSceneManager()->createEntity("ogre", "ogrehead.mesh");

	size_t vertex_count,index_count;
	Ogre::Vector3* vertices;
	unsigned long* indices;
	Ogre::Vector3 pos, ori, sca;
	Ogre::Vector3 position = Ogre::Vector3::ZERO;
	Ogre::Quaternion orient = Ogre::Quaternion::IDENTITY;
	Ogre::Vector3 scale = Ogre::Vector3::UNIT_SCALE;


	getMeshInformation(&complex->getMesh(),vertex_count,vertices,index_count,indices, position, orient, scale);
	btCollisionShape * CollisionShape = new btConvexHullShape();
	for ( int ii=0; ii<vertex_count; ++ii )
		static_cast<btConvexHullShape*>(CollisionShape)->addPoint( Vec3Physics(vertices[ii]) );

	
	ogrebody = BulletPhysicsMgr::getSingletonPtr()->createRigidBody(CollisionShape, 0.0f, btTransform(btQuaternion(0,0,0,1),btVector3(0,5,-20)));
	ogrebody->setUserPointer(0);	
	
	BulletPhysicsMgr::getSingletonPtr()->destroyRigidBody(ogrebody);
	delete CollisionShape;
	delete[] vertices;
	delete[] indices;
	


	--------------------------

	example usagte for btBvhTriangleMeshShape

	Ogre::Entity* complex = RenderEngine::getSingletonPtr()->getSceneManager()->createEntity("column", "column.mesh");

	size_t vertex_count,index_count;
	Ogre::Vector3* vertices;
	unsigned long* indices;
	Ogre::Vector3 pos, ori, sca;
	Ogre::Vector3 position = Ogre::Vector3::ZERO;
	Ogre::Quaternion orient = Ogre::Quaternion::IDENTITY;
	Ogre::Vector3 scale = Ogre::Vector3::UNIT_SCALE;

	getMeshInformation(complex,vertex_count,vertices,index_count,indices, position, orient, scale);

	btVector3* verts = new btVector3[vertex_count];
	for (int i=0; i<vertex_count; i++)
	{
		verts[i] = btVector3(vertices[i].x,vertices[i].y,vertices[i].z);
	}

	btTriangleMesh* trimesh = new btTriangleMesh();
	for( int i=0; i<vertex_count; i += 3)
	{
		trimesh->addTriangle(verts[i], verts[i+1], verts[i+2]);
	}

	btCollisionShape * CollisionShape = new btBvhTriangleMeshShape(trimesh, true);
	
	collision_shape_collection.push_back(CollisionShape);
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(10,20,10)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(0,fallMotionState,CollisionShape,fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);	
	dynamicsWorld->addRigidBody(fallRigidBody);

	*********************************************
	*************** DELETE ARRAYS ***************
	*********************************************
	delete [] vertices;
	delete [] indices;
	delete [] verts;

	... wjhenm destrouyinf shape:
	delete trimesh;
	del entity
	...


	notes:
		- no apparent mem leak detected

*/

