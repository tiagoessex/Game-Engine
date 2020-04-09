

// venator headers
#include "Grid.h"

// ogre headers
#include "OgreEntity.h"
#include "OgreMeshManager.h"
#include "OgreMaterialManager.h"
#include "OgreSceneManager.h"

using namespace Venator;
using namespace Venator::RenderEngine;

Grid::Grid(const std::string& name, Ogre::SceneManager* scenemgr, Scalar divisions, Scalar unit):
					Ogre::ManualObject(name),
					scenemgr(scenemgr),
					divisions(divisions),
					unit(unit)
{}


Grid::~Grid(void) {
	//material???????????
	if (myManualObjectNode)
		destroy();
}

void Grid::create(void) {
	Ogre::ManualObject* myManualObject =  scenemgr->createManualObject("gridmanualobj"); 
	myManualObjectNode = scenemgr->getRootSceneNode()->createChildSceneNode("gridmanualobj_node"); 
 
	Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("gridmanualobjmaterial","General"); 
	myManualObjectMaterial->setReceiveShadows(false); 
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,1,1,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(1,1,1); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,1,1); 
	//myManualObjectMaterial->dispose();  // dispose pointer, not the material
 
 
	myManualObject->begin("gridmanualobjmaterial", Ogre::RenderOperation::OT_LINE_LIST); 

	//divisions = 20;
	//unit = 1;

	// z dir
	for (int i=0; i<divisions+1; i++) {
		myManualObject->position(-divisions*unit/2 + i*unit, 0, -divisions*unit/2); 
		myManualObject->position(-divisions*unit/2 + i*unit, 0, divisions*unit/2);
	}
	
	// x dir
	for (int i=0; i<divisions+1; i++) {
		myManualObject->position(divisions*unit/2,0,-divisions*unit/2 + i*unit); 
		myManualObject->position(-divisions*unit/2,0,-divisions*unit/2 + i*unit);
	}


	myManualObject->position(0,-10,0);
	myManualObject->position(0,10,0);

	myManualObject->end(); 
	myManualObjectNode->attachObject(myManualObject);

}

void Grid::destroy(void) {	
	
	// clear mesh and node
	myManualObjectNode->detachObject(scenemgr->getManualObject("gridmanualobj"));	
	Ogre::MeshManager::getSingletonPtr()->remove("gridmanualobj");
	scenemgr->destroyManualObject("gridmanualobj");
	scenemgr->destroySceneNode(myManualObjectNode);

	// clear material
	Ogre::MaterialPtr mat2 = Ogre::MaterialManager::getSingleton().getByName("gridmanualobjmaterial");
	Ogre::MaterialManager::getSingleton().remove(mat2->getHandle());
	mat2.setNull();

}