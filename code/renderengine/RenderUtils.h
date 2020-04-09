

/*
	RenderUtils

	collections of usefull functions related with Ogre

	cleanings:
		void _destroyAllAttachedMovableObjects( Ogre::SceneNode* node )
		void clearSceneNode( Ogre::SceneNode* node )

	info:
		void _DumpNodes(std::stringstream &ss, Ogre::Node *n, int level)
		std::string DumpNodes(Ogre::Node *n)

	operations:
		Ogre::Vector3 getEntityBBCenter(Ogre::Entity* entity)


	others:
		Ogre::Vector3 getFitSize(Ogre::Entity* entity)

*/


#ifndef _RenderUtils_h_
#define _RenderUtils_h_

// venator headers
#include "../Prerequisites.h"

// c/c++ headers
#include <sstream>



namespace Ogre {
	class Node;
	class SceneNode;
	class Entity;
}


namespace Venator {
	namespace RenderEngine {

	/**
		internal of clearSceneNode
		to destroy all attrached objects in a node (entities, lights, particles, ... ) 
		and childs
	*/
	void _destroyAllAttachedMovableObjects( Ogre::SceneNode* node );

	/**
		calls destroyAllAttachedMovableObjects to detach and destroy all
		attached objects + destroys the node
	*/
	void clearSceneNode( Ogre::SceneNode* node );

	// internal of DumpNodes
	void _DumpNodes(std::stringstream &ss, Ogre::Node *n, int level);

	/**
		returns a string containing the tree structure starting from n
		ex:
		
			LOGINFO((DumpNodes(gameworld->scenemanager->getRootSceneNode())).c_str());
		=>

	Node Hierarchy:
	SceneNode: Ogre/SceneRoot
		  SceneNode: entity_0
				Entity: entity_0
				SceneNode: cameraNode
					  Camera: camera
				SceneNode: cannon1
				SceneNode: cannon2
		  SceneNode: player_shoots
				SceneNode: entity_3
					  Entity: entity_3
				SceneNode: entity_4
					  Entity: entity_4
				SceneNode: entity_5
					  Entity: entity_5
				SceneNode: entity_6
					  Entity: entity_6
				SceneNode: entity_7
					  Entity: entity_7
				SceneNode: entity_8
					  Entity: entity_8
		  SceneNode: gridmanualobj_node
				ManualObject: gridmanualobj
	*/
	std::string DumpNodes(Ogre::Node *n);


	/**
		returns entity's center coordinates conisdering boundingbox
	*/
	Vec3 getEntityBBCenter(Ogre::Entity* entity);



	/**
		returns an entity's bounding box size
			usefull for physics boundary set
	*/
	Vec3 getFitSize(Ogre::Entity* entity);


	}	// namespace renderengine
}		// namespace venator

#endif