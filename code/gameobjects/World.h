
// TO DO: VECTOR FOR SET

#ifndef __World_h_
#define __World_h_



#include <set>
#include <vector>

//#include "sigc++/sigc++.h"

#include "GameObjectCommon.h"
#include "GOBarker.h"
#include "../Prerequisites.h"

namespace Venator {
	namespace GameObjectComponentSystem {
		class ComponentsFactory;
		class GameObjectsManager;
		class SystemsManager;
		class GameObject;
		class Component;
		class BaseSystem;
		class TagsManager;
		class GameObjectsFactory;
		class GameObjectsParameters;
		class World;
	}
}

class Venator::GameObjectComponentSystem::World : public GOBarker
{
	
	public:	
		void initialise(void);
		void destroy(void);
		void reset(void);
		void clear(void);		// eliminate all gos from managers/...

		// update world - all active systems
		void updateWorldStart(const Scalar& deltaStart);
		void updateWorld(const Scalar& delta);
		void updateWorldEnd(const Scalar& deltaEnd);
	
		// world as the direct delta timer supplier => world used as global
		// in ogre set this times in FrameStarted, FrameEnded, FramerenderingQueue
		const Scalar& getDeltaStart(void) { return deltaStart; };
		const Scalar& getDelta(void) { return delta; };
		const Scalar& getDeltaEnd(void) { return deltaEnd; };
	

		// #################################
		// ########### GAME OBJECTS ########
		// #################################
		// ************ TEMPLATE CREATION *********
		GameObject* createGameObjectFromTemplate(const std::string& templatename);
		GameObject* createGameObjectFromTemplate(const std::string& templatename, const PARAMETERSMAP &parameters);
		// ************ MANUAL CREATION ***********
		// just create a go and return it
		GameObject* createGameObject(void);
		GameObject* createGameObject(const PARAMETERSMAP &parameters);
		// set to add to the world (add to goToAdd)
		// also start go (call start() of all components)
		void addGameObject(GameObject* go);
		// permanently delete go (add to goToEliminate)
		void deleteGameObject(GameObject* go);
		// get gameobject - only if already in the world
		GameObject* getGameObject(const LLG& id);

		// ############## EXPERIMENTAL ###############
		// remove go from world but do not delete it(add to goToRemove)
		// basically it just remove it from all systems
		void removeGameObject(GameObject* go);
		// reinsert the go
		// basically it just add it back to the systems
		// only used this if this go was removed using removeGameObject 
		void reInsertGameObject(GameObject* go);
		// #############################################

		PARAMETERSMAP getGOParameters(const std::string& name);

		// #################################
		// ########### COMPONENTS ##########
		// #################################
		/**
			get the component unique type ID
			if component doesn't exists yet => if add = true
			added it to the collection and assign it a new
			type ID
			if add = false and comp doesn't exist => return -1
		*/
		CPOS getComponentTypeID(const std::string& componentnameid);//, bool add = false);
		void addComponent(GameObject* go, Component* c);
		// permanently remove component from go and delete it
		void removeComponent(GameObject* go, Component* c);
		void removeComponent(GameObject* go, const CPOS& id);
		void removeComponent(GameObject* go, const std::string& component_name);
		// direct interface with componentsfactory
		Component* createComponent(const std::string& name);
		

		// #################################
		// ########### SYSTEMS #############
		// #################################
		// add system to manager
		void addSystem(BaseSystem* sys);
		// permanently delete system (add to systemToEliminate)
		void removeSystem(BaseSystem* go);
		void removeSystem(const std::string& sysName);
		BaseSystem* getSystem(const std::string& sysName);


		// #########################################
		// ########### GROUPS AND TAGS #############
		// #########################################

		void setTag(GameObject* go, const std::string& tag);
		void removeTag(GameObject* go, const std::string& tag);
		void removeTag(GameObject* go); // remove all tags of this go
		bool hasTag(GameObject* go,const std::string& tag);
		const std::string& getTag(GameObject* go);  // get first
		std::vector<GameObject*>& getGameObjectsWithTag(const std::string& tag);
		

		static World* getInstance( void );
		static World& getSingleton(void);
	private:	
		World(void);
		~World(void);
		World( const World& ) { }
		World & operator = ( const World& );
		static World *mWorld;

		// clear all collections
		// if any to create => delete them
		void _clearAll(void);

		ComponentsFactory* cFactory;
		GameObjectsManager* goManager;
		SystemsManager* sysManager;
		TagsManager* tagsManager;
		GameObjectsFactory* goFactory;
		GameObjectsParameters* goparameters;

		struct ComponentOp {
			GameObject* go;
			Component* comp;
		};

		// as set => if multiple same go to eliminate e.g. 2 shoots simultaneous against enemy
		// (same frame) => with set it will only eliminate once and not twice
		std::set <GameObject*> goCreated;		// to keep track of go created but not yet added
		std::set <GameObject*> goToEliminate;// entities to remove + delete from the world
		std::set <GameObject*> goToRemove;	// entities to remove from the world
		std::set <GameObject*>::iterator itergo;
	
		std::vector <ComponentOp> componentToEliminate;	// components to remove from the respective entities and world
		std::vector <ComponentOp>::iterator itercomp;


		std::vector <BaseSystem*> systemToEliminate;		// systems to remove from the world
		std::vector <BaseSystem*>::iterator itersystem;

		Scalar deltaStart, deltaEnd, delta;					// time between frames
	

};	// class World



#endif


/**
	world
	
	NOTES:
		- component ctor => set component's ID (bitset) <=> COMPONENTS in GameObjectsCommon.h
		- each time a go/component is added/removes => all manageers and systems are updated
		- uses DATAFILES.ENTITIES_TEMPLATES defined in GamesFiles.h to set GameObjectsFactory
			- list of components of each go
		- uses DATAFILES.PARAMETERS_TEMPLATES defined in GamesFiles.h to set GameObjectsParameters
			- list of default parameters for each go
			- when a new go is created one can get this param:
					PARAMETERSMAP param = World::getInstance()->getGOParameters("goxxxxx");
			  and use it in the creation:
					World::getInstance()->createGameObjectFromTemplate("goxxxxx",param);
			  ATT: these param can be overloaded with new values (this must be done before addGameObject)
					param["scale"] = "1,1,1";	// overwright template' scale					
		- when add GO to world => sets tag if any in parameters
		- after all init => registers components and systems



	ATT:
		- when system or component are added	** DO NOT CALL DELETE DIRECTLY **
		- after adding an entity to the world	** DO NOT CALL DELETE DIRECTLY **
		- USE WORLD TO CREATE COMPONENTS		** DO NOT CREATE COMPONENTS DIRECTLY **
		- USE WORLD TO CREATE GO				** DO NOT CREATE GO DIRECTLY **
		- USE WORLD TO ADD COMPONENTS
		- system creation:
			1 - create system ( id components to handle are set in system::Enter())
			2 - add system => sets system collection populating it with the go/component in current collections
		- to set components fields do it imediatly after its creation - ATT: there are components that
		  for complete setup require more manual values than just its fields. ex: render requires manager, 
		  node and pos/scale/orientation, otherwise it wil, assume default values

		- RESET vs CLEAR
			- RESET => ELIMINATE ALL WORLD: SYSTEMS, GOS, EVENTS, ...
			- CLEAR => ELIMINATE ALL GOS FROM ALL COLLECTIONS

	ex:

		World::getInstance()->initialise() ;	
		--------------- VAR 1 --------------
		PARAMETERSMAP param;
		param["mesh"]			= "player.mesh";
		param["position"]		= "0,10,0";	
		param["orientation"]	= "1,0,0,0";	
		param["initial_speed"]	= "20.0";
		g1 = World::getInstance()->createGameObject(param);
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("position"));	
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("render"));
		ComponentRender* c_render = static_cast<ComponentRender*> (g1->getComponent("render"));
		c_render->setSceneManager(manager);
		c_render->setSceneNode(playerMasterNode);
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("entity"));
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("speed"));
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("playercontrol"));
		--------------- VAR 2 --------------
		PARAMETERSMAP param;
		param["manager"]			= "primary";
		param["parent"]				= playerMasterNode->getName();
		param["mesh"]				= "player.mesh";
		param["position"]			= "0,10,0";	
		param["orientation"]		= "1,0,0,0";	
		param["initial_speed"]		= "20.0";
		param["collidershape"]		= "sphere";
		param["shape_sphere_radius"]= "5";
		param["kinematic"]			= "true";
		g1 = World::getInstance()->createGameObject(param);
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("position"));	
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("render"));
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("entity"));
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("speed"));
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("playercontrol"));
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("collider"));
		World::getInstance()->addComponent(g1,World::getInstance()->createComponent("rigidbody"));
		
		World::getInstance()->addGameObject(g1);


		// *** TEMPLATES ****
		<go name="go_4">
			<components>
				<component name="position"></component>											
				<component name="scale"></component>
				<component name="render"></component>
				<component name="entity"></component>
				<component name="velocity"></component>
				<component name="particles"></component>
			</components>		
		</go>	
		
			
		param.clear();
		param["entity"]			= "shoot.mesh";
		param["manager"]		= "primary";
		param["parent"]			= n->getName();
		param["scale"]			= "3,3,3";	
		param["speed"]			= "20.0";
		
		g1 = World::getInstance()->createGameObjectFromTemplate("go_4",param);		
		World::getInstance()->addGameObject(g1);

		

		<gos>
			<go name="playershoot">
				<speed>30</speed>
				<mesh>shoot.mesh</mesh>
				<scale>3,3,3</scale>
				<damagepower>10</damagepower>
				<lifespan>0.2</lifespan>
			</go>
		</gos>

		Ogre::SceneNode* playerShootsMasterNode = RenderManager::getInstance()->createNode(manager,manager->getRootSceneNode());
		PARAMETERSMAP param			= World::getInstance()->getGOParameters("playershoot");	
		param["manager"]			= "primary";
		param["parent"]				= playerShootsMasterNode->getName();
		param["position"]			= Utils::Vec32String(position);
		GameObject* g1				= World::getInstance()->createGameObjectFromTemplate("playershoot",param);
		
		World::getInstance()->addGameObject(g1);	


		//////////////////////////
		
		// manual creation
		GameObject* g1 = World::getInstance()->createGameObject();				// default params
		//GameObject* g1 = World::getInstance()->createGameObject(g);				// with params
		Component* c1 = World::getInstance()->createComponent("dummy");
		Component* c2 = World::getInstance()->createComponent("render");
		World::getInstance()->addComponent(g1,c1);
		World::getInstance()->addComponent(g1,c2);
		World::getInstance()->addComponent(g1,new ComponentJoder3("joder3"));
		World::getInstance()->addGameObject(g1);

		// from template
		GameObject* g2 = World::getInstance()->createGameObjectFromTemplate("go_2",g);
		World::getInstance()->addGameObject(g2);

		//////////////////////////


		World::getInstance()->addSystem(new DummySystem());		

		World::getInstance()->updateWorldStart(0);
		World::getInstance()->updateWorld(0);
		World::getInstance()->updateWorldEnd(0);

		World::getInstance()->destroy();
*/

