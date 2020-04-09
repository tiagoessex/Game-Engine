

// venator headers
#include "RenderUtils.h"
//#include "../Globals.h"

// ogre headers
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "OgreSceneManager.h"


using namespace Venator;
using namespace Venator::RenderEngine;


void Venator::RenderEngine::_destroyAllAttachedMovableObjects( Ogre::SceneNode* node )
{
	if (!node) { return; };
	
	// Destroy all the attached objects
	Ogre::SceneNode::ObjectIterator itObject = node->getAttachedObjectIterator();
   
	while ( itObject.hasMoreElements() ) {
		//LOGINFO(("### ITER MOVALBE IOBJECT DESTORYED > " + itObject.peekNextValue()->getName()).c_str());
		node->getCreator()->destroyMovableObject(itObject.getNext());
	}
   
	// Recurse to child SceneNodes
	Ogre::SceneNode::ChildNodeIterator itChild = node->getChildIterator();

	while ( itChild.hasMoreElements() )	{
		Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
		//LOGINFO(("### ITER NODE DESTORYED > " + pChildNode->getName()).c_str());
		Venator::RenderEngine::_destroyAllAttachedMovableObjects( pChildNode );
   }
}

void Venator::RenderEngine::clearSceneNode( Ogre::SceneNode* node ) 
{
	if(!node) { return; };
	Venator::RenderEngine::_destroyAllAttachedMovableObjects(node);	// detach + destroy the attachements
	node->removeAndDestroyAllChildren();	// destroys the nodes but not the attachements
	//LOGINFO(("### ITER MASTER NODE DESTORYED > " + node->getName()).c_str());
	node->getCreator()->destroySceneNode(node);
}


void Venator::RenderEngine::_DumpNodes(std::stringstream &ss, Ogre::Node *n, int level)
{
	for(int i = 0; i < level; i++) {
		ss << "   ";
	}
    ss << "SceneNode: " << n->getName() << std::endl;
 
	Ogre::SceneNode::ObjectIterator object_it = ((Ogre::SceneNode *)n)->getAttachedObjectIterator();
	Ogre::Node::ChildNodeIterator node_it = n->getChildIterator();
 
	Ogre::MovableObject *m;
	while(object_it.hasMoreElements()) {
		for(int i = 0; i < level + 2; i++) {
			ss << "   ";
		}
		m = object_it.getNext();
		ss << m->getMovableType() << ": " << m->getName() << std::endl;
	}
	while(node_it.hasMoreElements()) {
		Venator::RenderEngine::_DumpNodes(ss, node_it.getNext(), level + 2);
	}
}
 
std::string Venator::RenderEngine::DumpNodes(Ogre::Node *n)
{
	std::stringstream ss;
	ss << std::endl << "Node Hierarchy:" << std::endl;
	Venator::RenderEngine::_DumpNodes(ss, n, 0);
	return ss.str();
}


Vec3 Venator::RenderEngine::getEntityBBCenter(Ogre::Entity* entity) 
{
	const Ogre::AxisAlignedBox& bbox = entity->getWorldBoundingBox(true); 
	const Ogre::Vector3* corners = bbox.getAllCorners();
	return (corners[7].midPoint(corners[1]));
}


Vec3 Venator::RenderEngine::getFitSize(Ogre::Entity* entity) 
{
	const Ogre::AxisAlignedBox& bbox = entity->getWorldBoundingBox(true); 
	return (bbox.getSize() / 2.0f) * 0.96f;
}

