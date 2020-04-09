


#include "PlayState.h"
#include "PauseState.h"


#include "../Prerequisites.h"
#include "../utils/VenatorUtils.h"
#include "../renderengine/RenderManager.h"
#include "../gameobjects/World.h"

#include "../gameobjects/components/ComponentMeshAnimation.h"
#include "../gameobjects/components/ComponentRender.h"

#include "../renderengine/Grid.h"
#include "../renderengine/StaticText.h"
#include "../renderengine/RenderUtils.h"


#include "Ogre.h"
/*
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreCamera.h"
#include "OgreRenderWindow.h"
#include "OgreMeshManager.h"
#include "OgreRoot.h"
#include "OgreStaticGeometry.h"
*/

#include "../physics/BulletPhysicsMgr.h"
#include "../events/EventsDispatcher.h"


#include "../sound/SoundManager.h"
#include "../sound/Sound3D.h"

#include "IntroState.h"

#include "../renderengine/NodeAnimation.h"
#include "../GameFiles.h"

#if (_DEBUG_)
#include "../DebugShits.h"
#endif



using namespace Venator;
using namespace Venator::GameStates;
using namespace Venator::RenderEngine;
using namespace Venator::GameObjectComponentSystem;
using namespace Venator::PhysicsSystem;
using namespace Venator::Events;
using namespace Venator::SoundSystem;


Ogre::String buildInstancedMaterial(const Ogre::String &originalMaterialName)
{
	if (Ogre::StringUtil::endsWith(originalMaterialName,"/instanced"))
	{
		return originalMaterialName;
	}

	Ogre::MaterialPtr originalMaterial = Ogre::MaterialManager::getSingleton().getByName(originalMaterialName);
	const Ogre::String instancedMaterialName(originalMaterial.isNull() ? "Instancing" : originalMaterialName + "/Instanced");
	Ogre::MaterialPtr instancedMaterial = Ogre::MaterialManager::getSingleton().getByName(instancedMaterialName);
	if (instancedMaterial.isNull())
	{
		instancedMaterial = originalMaterial->clone(instancedMaterialName);
		instancedMaterial->load();
		Ogre::Technique::PassIterator pIt = instancedMaterial->getBestTechnique()->getPassIterator();
		while(pIt.hasMoreElements())
		{
			Ogre::Pass * const p = pIt.getNext();
			p->setVertexProgram("Instancing",false);
			p->setShadowCasterVertexProgram("InstancingShadowCaster");
			
			
		}
	}
	instancedMaterial->load();
	return instancedMaterialName;
}

void setupInstancedMaterialToEntity(Ogre::Entity *ent)
{
	for (Ogre::uint i=0;i<ent->getNumSubEntities();++i)
	{
		Ogre::SubEntity * se = ent->getSubEntity(i);
		Ogre::String materialName = se->getMaterialName();
		se->setMaterialName(buildInstancedMaterial(materialName));
	}
}


PlayState::PlayState(void) :
					grid(0),
					flag_start_test(false)
{
	LOGTORS("************ PlayState CTOR ************");
	ID++;
#if _DEBUG_
	debug = 0;
#endif
} 

PlayState::~PlayState(void) 
{
	LOGTORS("************ PlayState DTOR ************");
}

void PlayState::onENTER()
{
	LOGINFO("[PlayState::onENTER] PlayState onENTER");


	
	EventsDispatcher::getInstance()->registerListener(*this,COLLISIONHIT);
		
	manager = RenderManager::getInstance()->getSceneManager("primary");
	manager->getRootSceneNode()->createChildSceneNode("player");
	manager->getRootSceneNode()->createChildSceneNode("enemies");

	LOGINFO("%%%%%%%% START PLAYSTATE %%%%%%%%%%%%");
	LOGINFO((DumpNodes(manager->getRootSceneNode())).c_str());
	LOGINFO("%%%%%%%%%%%%%%%%%%%%%%%%%%%%");

	// camera
	Ogre::SceneNode* cameraNode = manager->getRootSceneNode()->createChildSceneNode("cameraNode");
	cameraNode->attachObject(manager->getCamera("camera"));	
	manager->getSceneNode("cameraNode")->setPosition(0,50,40);
	manager->getSceneNode("cameraNode")->lookAt(Vec3(0,0,0),Ogre::Node::TS_WORLD);
		

#if _DEBUG_
	debug = new Debug::DebugShits();
	debug->initialise(manager);
	debug->setDebugCamera(cameraNode);
	grid = new Venator::RenderEngine::Grid("grid", manager, 10, 5);
	grid->create();
#endif


	RenderManager::getInstance()->loadAnimations(DATAFILES.ANIMATIONS.c_str(),manager);
/*
	PARAMETERSMAP param = World::getInstance()->getGOParameters("playership");;
	param["manager"]			= "primary";
	param["parent"]				= "player";
	param["position"]			= "0,10,0";	
	g1 = World::getInstance()->createGameObjectFromTemplate("playership",param);		
	World::getInstance()->addGameObject(g1);
	*/
	/*
PARAMETERSMAP param = World::getInstance()->getGOParameters("playership");
	param["manager"]			= "primary";
	param["parent"]				= "player";
	param["position"]			= "0,10,0";	
	g1 = World::getInstance()->createGameObjectFromTemplate("playership",param);		
	World::getInstance()->addGameObject(g1);

	
	param = World::getInstance()->getGOParameters("enemyship");;
	param["manager"]			= "primary";
	param["parent"]				= "enemies";
	param["position"]			= "10,10,0";	
	g2 = World::getInstance()->createGameObjectFromTemplate("enemyship",param);		
	World::getInstance()->addGameObject(g2);
	

	param = World::getInstance()->getGOParameters("object_animnode");;
	param["manager"]			= "primary";
	param["parent"]				= "enemies";
	param["position"]			= "-10,-10,0";	
	g2 = World::getInstance()->createGameObjectFromTemplate("object_animnode",param);		
	World::getInstance()->addGameObject(g2);
	


	param = World::getInstance()->getGOParameters("object1");
	param["manager"]			= "primary";
	param["parent"]				= "player";
	param["position"]			= "0,30,0";	
	g1 = World::getInstance()->createGameObjectFromTemplate("object1",param);		
	World::getInstance()->addGameObject(g1);

	BulletPhysicsMgr::getInstance()->setDebugDraw(manager);
	BulletPhysicsMgr::getInstance()->setGravity(Vec3(0,-10,0));
	
	*/

//	Ogre::MeshPtr meshReference = Ogre::MeshManager::getSingleton().load( "robot.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME );
	Ogre::Entity* ogreHead = manager->createEntity("Head", "ogrehead.mesh"); 
	
		setupInstancedMaterialToEntity(ogreHead);	
	Ogre::InstancedGeometry* qwe = manager->createInstancedGeometry("heads");
	
	for (int i=0; i<25; i++)
		qwe->addEntity(ogreHead, Ogre::Vector3(-40 + 10*i,0,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	

	qwe->setBatchInstanceDimensions (Ogre::Vector3(100000, 100000, 100000));

  qwe->setOrigin(Ogre::Vector3::ZERO);
  qwe->build();

  Ogre::InstancedGeometry::BatchInstanceIterator batch = qwe->getBatchInstanceIterator();
  Ogre::InstancedGeometry::BatchInstanceMap::const_iterator it = batch.begin();
  Ogre::InstancedGeometry::BatchInstanceMap::const_iterator end = batch.end();

  for ( ; it != end; it++ )
  {    
    //Ogre::SceneNode * node = static_cast<Ogre::SceneNode*>(it->second->getParentNode());
   // node->showBoundingBox(true);
    
    Ogre::InstancedGeometry::BatchInstance::InstancedObjectIterator bit = it->second->getObjectIterator();
    int j = 0;
	int k = 0;
    while(bit.hasMoreElements())
    {
      Ogre::InstancedGeometry::InstancedObject* obj = bit.getNext();obj;
	  //instances.push_back(obj);
	  obj->setPosition(Ogre::Vector3(5*j,5*k,0));      
	  obj->setScale(Ogre::Vector3(0.1,0.1,0.1));
      ++j;
	  if (j == 4) { j = 0; k++; }

    }
  }

  qwe->addBatchInstance();
  qwe->setVisible(true);
  
  bool visible = qwe->isVisible();visible;
  float dist = qwe->getRenderingDistance();dist;
  manager->destroyEntity(ogreHead);


}




void PlayState::onEXIT()
{
	LOGINFO("[PlayState::onEXIT] PlayState onEXIT");
	

#if _DEBUG_
	debug->destroy();
	delete debug;
	if (grid)				{ delete grid; }
#endif
	
	manager->getSceneNode("cameraNode")->detachObject(manager->getCamera("camera"));	
	//RenderManager::getInstance()->destroyNode(manager->getSceneNode("cameraNode"));
	manager->destroySceneNode(manager->getSceneNode("cameraNode"));

	LOGINFO("%%%%%%%%%% EXIT PLAYSTATE %%%%%%%%%%%%");
	LOGINFO((DumpNodes(manager->getRootSceneNode())).c_str());
	LOGINFO("%%%%%%%%%%%%%%%%%%%%%%%%%%%%");


	EventsDispatcher::getInstance()->unRegisterListener(*this);
}

void PlayState::onPAUSE()
{
	LOGINFO("[PlayState::onPAUSE] PlayState onPAUSE");
}

void PlayState::onRESUME()
{
	LOGINFO("[PlayState::onRESUME] PlayState onRESUME");
}

bool PlayState::keyPressed( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
		case OIS::KC_P:
			//pushState(new PauseState());
			sg->reset();
			break;	

		case OIS::KC_Q:
			for (int i=0; i<5; i++)
			{
				for (int k=0; k<5; k++)
				{
					sg->addEntity(manager->getEntity("Head"), Ogre::Vector3(5*i,5*k,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
				}
			}
			sg->build();
			break;
		case OIS::KC_4:
			{
				ComponentMeshAnimation* c = static_cast<ComponentMeshAnimation*>
					(g2->getComponent(MESHANIMATION));
				if (c)  c->setAnimation("Attack1");	

			}
			break;
		case OIS::KC_5:
			{
				ComponentMeshAnimation* c = static_cast<ComponentMeshAnimation*>
					(g2->getComponent(MESHANIMATION));
				if (c) c->setAnimation("Death1");				
			}
			break;
		default:
			break;
	}
	return true;
}

bool PlayState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return true;
}

bool PlayState::mouseMoved(const OIS::MouseEvent &arg)
{
	return true;
}

bool PlayState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

bool PlayState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}


bool PlayState::updateStart(const Scalar& dt)
{	

	World::getInstance()->updateWorldStart(dt);
	return true;
}

bool PlayState::update(const Scalar& dt)
{
	World::getInstance()->updateWorld(dt);

#if _DEBUG_
	debug->update(dt);
#endif

	//mLightAnimationState->addTime(dt);

	return true;
}

bool PlayState::updateEnd(const Scalar& dt)
{
	World::getInstance()->updateWorldEnd(dt);
	return true;
}




void PlayState::receiveEvent(EVENTS ev, Event* info) {
	switch (ev) {
		case COLLISIONHIT:
			{
				HitInfo* inf = static_cast<HitInfo*> (info);
				GameObject* o1 = inf->object1;
				GameObject* o2 = inf->object2;
				std::string tag1 = World::getInstance()->getTag(o1);  
				std::string tag2 = World::getInstance()->getTag(o2);			
			}
			break;
		default: break;
	}
}


//////////////////////////////////////////
// INSTANCE

/*

Ogre::String buildInstancedMaterial(const Ogre::String &originalMaterialName)
{
	if (Ogre::StringUtil::endsWith(originalMaterialName,"/instanced"))
	{
		return originalMaterialName;
	}

	Ogre::MaterialPtr originalMaterial = Ogre::MaterialManager::getSingleton().getByName(originalMaterialName);
	const Ogre::String instancedMaterialName(originalMaterial.isNull() ? "Instancing" : originalMaterialName + "/Instanced");
	Ogre::MaterialPtr instancedMaterial = Ogre::MaterialManager::getSingleton().getByName(instancedMaterialName);
	if (instancedMaterial.isNull())
	{
		instancedMaterial = originalMaterial->clone(instancedMaterialName);
		instancedMaterial->load();
		Ogre::Technique::PassIterator pIt = instancedMaterial->getBestTechnique()->getPassIterator();
		while(pIt.hasMoreElements())
		{
			Ogre::Pass * const p = pIt.getNext();
			p->setVertexProgram("Instancing",false);
			p->setShadowCasterVertexProgram("InstancingShadowCaster");
			
		}
	}
	instancedMaterial->load();
	return instancedMaterialName;
}

void setupInstancedMaterialToEntity(Ogre::Entity *ent)
{
	for (Ogre::uint i=0;i<ent->getNumSubEntities();++i)
	{
		Ogre::SubEntity * se = ent->getSubEntity(i);
		Ogre::String materialName = se->getMaterialName();
		se->setMaterialName(buildInstancedMaterial(materialName));
	}
}





/*
	setupInstancedMaterialToEntity(ogreHead);	
	Ogre::InstancedGeometry* qwe = manager->createInstancedGeometry("heads");
	
	for (int i=0; i<25; i++)
		qwe->addEntity(ogreHead, Ogre::Vector3(-40 + 10*i,0,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	

	qwe->setBatchInstanceDimensions (Ogre::Vector3(100000, 100000, 100000));

  qwe->setOrigin(Ogre::Vector3::ZERO);
  qwe->build();

  Ogre::InstancedGeometry::BatchInstanceIterator batch = qwe->getBatchInstanceIterator();
  Ogre::InstancedGeometry::BatchInstanceMap::const_iterator it = batch.begin();
  Ogre::InstancedGeometry::BatchInstanceMap::const_iterator end = batch.end();

  for ( ; it != end; it++ )
  {    
    //Ogre::SceneNode * node = static_cast<Ogre::SceneNode*>(it->second->getParentNode());
   // node->showBoundingBox(true);
    
    Ogre::InstancedGeometry::BatchInstance::InstancedObjectIterator bit = it->second->getObjectIterator();
    int j = 0;
	int k = 0;
    while(bit.hasMoreElements())
    {
      Ogre::InstancedGeometry::InstancedObject* obj = bit.getNext();obj;
	  obj->setPosition(Ogre::Vector3(5*j,5*k,0));      
	  obj->setScale(Ogre::Vector3(0.1,0.1,0.1));
      ++j;
	  if (j == 4) { j = 0; k++; }

    }
  }

  qwe->addBatchInstance();
  qwe->setVisible(true);
  
  bool visible = qwe->isVisible();visible;
  float dist = qwe->getRenderingDistance();dist;
  manager->destroyEntity(ogreHead);
  */

//////////////////////////////////////////






	/* 260fps
	Ogre::Entity* ogreHead = manager->createEntity("Head", "ogrehead.mesh"); 

	Ogre::StaticGeometry *sg = manager->createStaticGeometry("static_geos");
	sg->setRegionDimensions(Ogre::Vector3(50, 50, 50));
	sg->setOrigin(Ogre::Vector3(0, 0, 0));	
	for (int i=0; i<5; i++)
	{
		for (int k=0; k<5; k++)
		{
			sg->addEntity(ogreHead, Ogre::Vector3(5*i,5*k,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
		}
	}
	sg->build();
	*/


//	Ogre::Entity* ogreHead = manager->createEntity("Head", "ogrehead.mesh"); 

/*	renderInstance.reserve(mNumRendered);
	renderInstance.resize(mNumRendered);
*/
	//Ogre::InstancedGeometry * batch = new Ogre::InstancedGeometry(manager,"instancing");
	
	//batch->setBatchInstanceDimensions(Ogre::Vector3(100000,100000,100000));
	//const size_t batchSize = 10; //(mNumMeshes > maxObjectsPerBatch) ? maxObjectsPerBatch : mNumMeshes;
	/*
	setupInstancedMaterialToEntity(ogreHead);	
	Ogre::InstancedGeometry* qwe = manager->createInstancedGeometry("heads");
	qwe->addEntity(ogreHead, Ogre::Vector3(0,0,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	qwe->addEntity(ogreHead, Ogre::Vector3(10,10,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	qwe->addEntity(ogreHead, Ogre::Vector3(20,10,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	qwe->addEntity(ogreHead, Ogre::Vector3(30,10,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	qwe->addEntity(ogreHead, Ogre::Vector3(40,10,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	qwe->addEntity(ogreHead, Ogre::Vector3(-40,10,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	qwe->addEntity(ogreHead, Ogre::Vector3(-30,10,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	qwe->addEntity(ogreHead, Ogre::Vector3(-20,10,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	qwe->addEntity(ogreHead, Ogre::Vector3(-10,10,0), Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	

	qwe->setBatchInstanceDimensions (Ogre::Vector3(100000, 100000, 100000));

  qwe->setOrigin(Ogre::Vector3::ZERO);
  qwe->build();

  Ogre::InstancedGeometry::BatchInstanceIterator batch = qwe->getBatchInstanceIterator();
  Ogre::InstancedGeometry::BatchInstanceMap::const_iterator it = batch.begin();
  Ogre::InstancedGeometry::BatchInstanceMap::const_iterator end = batch.end();

  for ( ; it != end; it++ )
  {    
    Ogre::SceneNode * node = static_cast<Ogre::SceneNode*>(it->second->getParentNode());
    node->showBoundingBox(true);
    
    Ogre::InstancedGeometry::BatchInstance::InstancedObjectIterator bit = it->second->getObjectIterator();
    int j = 0;
    while(bit.hasMoreElements())
    {
      Ogre::InstancedGeometry::InstancedObject* obj = bit.getNext();obj;
	  obj->setPosition(Ogre::Vector3(0,j*10,0));       
      //obj->setPosition(Ogre::Vector3::ZERO);
      ++j;

    }
  }

  qwe->addBatchInstance();
  qwe->setVisible(true);
  
  bool visible = qwe->isVisible();visible;
  float dist = qwe->getRenderingDistance();dist;
  manager->destroyEntity(ogreHead);
  */
	/*
	qwe->build();
	
	Ogre::InstancedGeometry::BatchInstanceIterator regIt = qwe->getBatchInstanceIterator();
	while (regIt.hasMoreElements()) {
		Ogre::InstancedGeometry::BatchInstance * r = regIt.getNext();
		Ogre::InstancedGeometry::BatchInstance::InstancedObjectIterator bit = r->getObjectIterator();
		int j=0;
		while (bit.hasMoreElements())
		{
			Ogre::InstancedGeometry::InstancedObject* obj = bit.getNext();
			LOGINFO("*****");
			obj->setScale(Ogre::Vector3(0.1,0.1,0.1));
			obj->setPosition(Ogre::Vector3(j*10,0,0));
			LOGINFO((Venator::Utils::Vec32String(obj->getPosition())).c_str());

		}
	}

	//qwe->addBatchInstance();
	qwe->setVisible(true);
	*/


	/*

	for (size_t i=0;i<batchSize;i++)
	{
		batch->addEntity(ogreHead, Ogre::Vector3::ZERO);//, Ogre::Quaternion(Ogre::Quaternion::IDENTITY), Ogre::Vector3(0.1,0.1,0.1));
	}
	batch->setOrigin(Ogre::Vector3::ZERO);
	batch->build();
	
	for (size_t k=0;k<2;k++)
	{
		batch->addBatchInstance();
	}

	Ogre::InstancedGeometry::BatchInstanceIterator regIt = batch->getBatchInstanceIterator();
	size_t k=0;
	while (regIt.hasMoreElements())
	{
		Ogre::InstancedGeometry::BatchInstance * r = regIt.getNext();
		Ogre::InstancedGeometry::BatchInstance::InstancedObjectIterator bit = r->getObjectIterator();
		int j=0;
		while (bit.hasMoreElements())
		{
			Ogre::InstancedGeometry::InstancedObject* obj = bit.getNext();
			const Ogre::Vector3 position (5*k, 5*j,0);
			obj->setPosition(position);
			obj->setScale(Ogre::Vector3(0.1,0.1,0.1));
			++j;
		}
		k++;
	}
	batch->setVisible(true);
//	renderInstance[0] = batch;
	manager->destroyEntity(ogreHead);

 // mInstancedGeometry->addBatchInstance();
 // mInstancedGeometry->setVisible(true);
  */
 
