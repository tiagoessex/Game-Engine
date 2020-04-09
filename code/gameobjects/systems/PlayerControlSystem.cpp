

#include "PlayerControlSystem.h"
#include "../GameObject.h"
#include "../World.h"
#include "../components/ComponentPosition.h"
#include "../components/ComponentSpeed.h"
#include "../components/ComponentPlayerControl.h"
//#include "../components/ComponentOrientation.h"

#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"
#include "../../InputManager.h"

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "OgreMath.h"



using namespace Venator;

using namespace Venator::GameObjectComponentSystem;



PlayerControlSystem::PlayerControlSystem(void) : 
					BaseSystem("PlayerControlSystem"),
					input_manager(0)
{
	LOGTORS("************ PlayerControlSystem CTOR ************");	
}
	
PlayerControlSystem::~PlayerControlSystem(void) {
	LOGTORS("************ PlayerControlSystem DTOR ************");
}


void PlayerControlSystem::enter() {
	LOGINFO("[PlayerControlSystem::enter] PlayerControlSystem enter");	
	handleComponent("position");
	handleComponent("speed");	
	handleComponent("playercontrol");	
//	handleComponent("orientation");

	input_manager = InputEngine::InputManager::getInstance();

	//c = shoot.connect( sigc::ptr_fun(Venator::Actions::playerShoot) );
}

void PlayerControlSystem::update(GameObject* go) {
	static bool ready_to_shoot = true;
	static bool no_shoot = false;
	Scalar tick = World::getInstance()->getDelta();

	ComponentPosition* pos = 0;
	pos = static_cast<ComponentPosition*> (go->getComponent(POSITION));
	ComponentSpeed* sp = 0;
	sp = static_cast<ComponentSpeed*> (go->getComponent(SPEED));

	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_UP)) {
		if (pos->position.z > -20) {
			pos->position.z -= sp->current_speed * tick;
		}
	}
	
	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_DOWN)) {
		if (pos->position.z < 20) {
			pos->position.z += sp->current_speed * tick;
		}
	}
	
	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_LEFT)) {	
		if (pos->position.x > -20) {
			pos->position.x -= sp->current_speed * tick;
		}
	}
	
	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_RIGHT)) {	
		if (pos->position.x < 20) {
			pos->position.x += sp->current_speed * tick;
		}
	}

	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_SPACE)) {	
		if (!ready_to_shoot) { return; }
		//shoot.emit(pos->position);	
		_shoot(pos->position);
		no_shoot = true;
		ready_to_shoot = false;
	} else {
		if (ready_to_shoot) { return; }
		ready_to_shoot = true; 
		no_shoot = false;
	}
}

void PlayerControlSystem::_shoot(Vec3& position) {
	PARAMETERSMAP param = World::getInstance()->getGOParameters("playershoot");	
	param["manager"] = "primary";
	param["parent"] = "playershoots";
	param["position"] = Utils::Vec32String(position);
	GameObject* g1 = World::getInstance()->createGameObjectFromTemplate("playershoot",param);
	World::getInstance()->addGameObject(g1);	
}

void PlayerControlSystem::exit() {
	LOGINFO("[PlayerControlSystem::exit] PlayerControlSystem exit");
	//c.disconnect();
}


/**		PLAYER WITH ROTATION AND DIRECTION

void PlayerControlSystem::update(GameObject* go) {
	static bool ready_to_shoot = true;
	static bool no_shoot = false;

	ComponentPosition* pos = 0;
	pos = static_cast<ComponentPosition*> (go->getComponent(POSITION));
	ComponentPlayerControl* pc = 0;
	pc = static_cast<ComponentPlayerControl*> (go->getComponent(PLAYERCONTROL));
	ComponentOrientation* ori = 0;
	ori = static_cast<ComponentOrientation*> (go->getComponent(ORIENTATION));
	ComponentSpeed* sp = 0;
	sp = static_cast<ComponentSpeed*> (go->getComponent(SPEED));

	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_UP)) {
		Vec3 deslocation = ori->orientation * Vec3(0,0,-sp->current_speed * World::getInstance()->getDelta());
		pos->position = pos->position + deslocation;

	}
	
	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_DOWN)) {
		Vec3 deslocation = ori->orientation * Vec3(0,0,sp->current_speed * World::getInstance()->getDelta());
		pos->position = pos->position + deslocation;
	}
	
	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_LEFT)) {
		Ogre::Quaternion q = Ogre::Quaternion(Ogre::Degree(10.0f) *  World::getInstance()->getDelta() * sp->current_speed, Ogre::Vector3::UNIT_Y);
		ori->orientation = q * ori->orientation;
	}
	
	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_RIGHT)) {
		Ogre::Quaternion q = Ogre::Quaternion(-Ogre::Degree(10.0f) *  World::getInstance()->getDelta() * sp->current_speed, Ogre::Vector3::UNIT_Y);
		ori->orientation = q * ori->orientation;
	}

	if(input_manager->getKeyboard()->isKeyDown(OIS::KC_SPACE)) {	
		if (!ready_to_shoot) { return; }
	
		ComponentRender* render = 0;
		render = static_cast<ComponentRender*> (go->getComponent(RENDER));
		if (!render) { return; }
		shoot.emit(pos->position, ori->orientation * Vec3::NEGATIVE_UNIT_Z, render->getSceneManager());	
		no_shoot = true;
		ready_to_shoot = false;
	} else {
		if (ready_to_shoot) { return; }
		ready_to_shoot = true; 
		no_shoot = false;
	}
}


*/
