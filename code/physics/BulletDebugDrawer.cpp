
// venator headers
#include "BulletDebugDrawer.h"
//#include "../Globals.h"
#include "../renderengine/RenderUtils.h"

// ogre headers
#include <OgreMaterialManager.h>
#include <OgreRoot.h>
#include <OgreTextureUnitState.h>
#include <OgreMeshManager.h>
#include <OgreManualObject.h>
#include <OgreSceneManager.h>



using namespace Venator;
using namespace Venator::PhysicsSystem;


const char * OgreDebugDrawer::matName = "OgreBulletCollisionsDebugDefault";
  

OgreDebugDrawer::OgreDebugDrawer( Ogre::SceneManager *scm, btScalar contact_point_distance ) : 
								scm(scm), 
								contact_point_distance(contact_point_distance)
{
	Ogre::SceneNode* masternode = scm->getRootSceneNode()->createChildSceneNode("physics_debug_node");

	// material
	Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("physics_debug_material","General"); 
	myManualObjectMaterial->setReceiveShadows(false); 
    myManualObjectMaterial->setSceneBlending( Ogre::SBT_TRANSPARENT_ALPHA );
    myManualObjectMaterial->setDepthBias( 0.1f, 0 );
    Ogre::TextureUnitState * tu = myManualObjectMaterial->getTechnique(0)->getPass(0)->createTextureUnitState();
    tu->setColourOperationEx( Ogre::LBX_SOURCE1, Ogre::LBS_DIFFUSE );
    myManualObjectMaterial->getTechnique(0)->setLightingEnabled(false);

	// line
	lines =  scm->createManualObject(); 
	myManualObjectNode = scm->getSceneNode("physics_debug_node")->createChildSceneNode(); 
	lines->begin("physics_debug_material", Ogre::RenderOperation::OT_LINE_LIST); 
	myManualObjectNode->attachObject(lines);
	lines->setDynamic(true);
	lines->position(0,0,0);
	lines->colour(0,0,1);
	lines->position(0,0,0);
	lines->colour(0,0,1);
	

	// triangle
	triangles =  scm->createManualObject(); 
	myManualObjectNode2 = scm->getSceneNode("physics_debug_node")->createChildSceneNode(); 
	triangles->begin("physics_debug_material", Ogre::RenderOperation::OT_TRIANGLE_LIST); 
	myManualObjectNode2->attachObject(triangles);
	triangles->setDynamic(true);
	triangles->position(0,0,0);
	triangles->colour(0,0,1);
	triangles->position(0,0,0);
	triangles->colour(0,0,1);
	triangles->position(0,0,0);
	triangles->colour(0,0,1);

	// mode
    mDebugModes = (DebugDrawModes) DBG_DrawWireframe;

}
 
OgreDebugDrawer::~OgreDebugDrawer()
{	
	
	// detach manual meshes from nodes
	myManualObjectNode->detachObject(lines);	
	myManualObjectNode2->detachObject(triangles);	

	// destroy manual meshes - overkill - no need clearSceneNode clears this shit
	Ogre::MeshManager::getSingletonPtr()->remove(lines->getName());
	Ogre::MeshManager::getSingletonPtr()->remove(triangles->getName());
	scm->destroyManualObject(lines->getName());
	scm->destroyManualObject(triangles->getName());
	
	// clear all nodes and attached objects
	Venator::RenderEngine::clearSceneNode(scm->getSceneNode("physics_debug_node"));
	
	//clearSceneNode(scm->getSceneNode("physics_debug_node"));

	// clear material
	Ogre::MaterialPtr mat2 = Ogre::MaterialManager::getSingleton().getByName("physics_debug_material");
	Ogre::MaterialManager::getSingleton().remove(mat2->getHandle());
	mat2.setNull();
	

	// just in case
	lines = 0;
	triangles = 0;

}
 
void OgreDebugDrawer::drawLine( const btVector3 &from, const btVector3 &to, const btVector3 &color )
{
	lines->position(from[0],from[1],from[2]);
	//lines->colour(color[0],color[2],color[2]);
	lines->colour(1,1,0);
	lines->position(to[0],to[1],to[2]);
	//lines->colour(color[0],color[2],color[2]);
	lines->colour(1,1,0);
}
 
void OgreDebugDrawer::drawTriangle( const btVector3 &v0, const btVector3 &v1, const btVector3 &v2, const btVector3 &color, btScalar alpha )
{
	triangles->position(v0[0],v0[1],v0[2]);
	//triangles->colour(color[0],color[2],color[2]);
	triangles->colour(1,0,1);
	triangles->position(v1[0],v1[1],v1[2]);
	//triangles->colour(color[0],color[2],color[2]);
	triangles->colour(1,0,1);
	triangles->position(v2[0],v2[1],v2[2]);
	//triangles->colour(color[0],color[2],color[2]);
	triangles->colour(1,0,1);
}
 
void OgreDebugDrawer::drawContactPoint( const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color )
{
	btVector3 to(PointOnB + normalOnB * contact_point_distance);//*distance * 100000);
	lines->position(PointOnB[0],PointOnB[1],PointOnB[2]);
	lines->colour(1,0,0);
	lines->position(to[0],to[1],to[2]);
	lines->colour(1,0,0);
}
 
void OgreDebugDrawer::updateStart( void )
{
	lines->end(); 
	triangles->end(); 
}
 
void OgreDebugDrawer::updateEnd( void )
{
	lines->beginUpdate(0);	
	triangles->beginUpdate(0);
}
 

void OgreDebugDrawer::reportErrorWarning( const char *warningString )
{
}


void OgreDebugDrawer::setDebugMode( int debugMode )
{
    mDebugModes = (DebugDrawModes) debugMode;
}
 
int OgreDebugDrawer::getDebugMode() const
{
    return mDebugModes;
}