

/**

	

	usage:

		Ogre::Entity* complex = RenderEngine::getSingletonPtr()->getSceneManager()->createEntity("column", "column.mesh");
		Ogre::SceneNode* cubeNode2 = RenderEngine::getSingletonPtr()->getSceneManager()->getRootSceneNode()->createChildSceneNode("cube2222");
		cubeNode2->attachObject(complex);
		cubeNode2->setScale(3,3,3);
		cubeNode2->setPosition(0,1,10);
		MeshStrider* Strider = new MeshStrider(complex->getMesh().get());
		btCollisionShape* CollisionShape = new btBvhTriangleMeshShape(Strider,true,true);
	or:
		[Ogre::Entity* complex = RenderEngine::getSingletonPtr()->getSceneManager()->createEntity("column", "column.mesh");] // no need
		Ogre::MeshPtr MeshPtr = Ogre::Singleton<Ogre::MeshManager>::getSingletonPtr()->load("column.mesh", "Popular");
		MeshStrider* Strider = new MeshStrider(MeshPtr.get());
		btCollisionShape* CollisionShape = new btBvhTriangleMeshShape(Strider,true,true);
	
	---

		collision_shape_collection.push_back(CollisionShape);
		btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,5,0)));
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(0,fallMotionState,CollisionShape,fallInertia);
		btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);		
		dynamicsWorld->addRigidBody(fallRigidBody);

	...
		
		// when no more needed
		delete Strider;
		del entitty
		...

		ATT: 
				- scale 1:1
				- no apparent mem leak detected
				- MeshPtr can be used by many
				- meshptr is a shared ptr => only when there is no ref to it, is the resource freed

*/

#ifndef MeshStrider_h__
#define MeshStrider_h__
 
#include <btBulletDynamicsCommon.h>

 
namespace Ogre
{
	class Mesh;
}


namespace Venator
{

	/// Shares vertices/indexes between Ogre and Bullet
	class MeshStrider : public btStridingMeshInterface
	{
 
		public:
			MeshStrider( Ogre::Mesh * m = 0 ) : mMesh(m){}
 
			void set( Ogre::Mesh * m ) 
			{ 
				//ASSERT(m); 
				mMesh = m; 
			}

			// inherited interface
			virtual int		getNumSubParts() const;
 
			virtual void    getLockedVertexIndexBase(unsigned char **vertexbase, int& numverts,PHY_ScalarType& type, int& stride,unsigned char **indexbase,int & indexstride,int& numfaces,PHY_ScalarType& indicestype,int subpart=0);
			virtual void    getLockedReadOnlyVertexIndexBase(const unsigned char **vertexbase, int& numverts,PHY_ScalarType& type, int& stride,const unsigned char **indexbase,int & indexstride,int& numfaces,PHY_ScalarType& indicestype,int subpart=0) const;
 
			virtual void    unLockVertexBase(int subpart);
			virtual void    unLockReadOnlyVertexBase(int subpart) const;
 
			virtual void    preallocateVertices(int numverts);
			virtual void    preallocateIndices(int numindices);
		private:
			Ogre::Mesh * mMesh;
	};

}

#endif // MeshStrider_h__