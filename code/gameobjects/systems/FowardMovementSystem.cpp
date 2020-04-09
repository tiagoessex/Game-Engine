

#include "FowardMovementSystem.h"
#include "../GameObject.h"
#include "../World.h"
#include "../components/ComponentPosition.h"
#include "../components/ComponentSpeed.h"
#include "../components/ComponentOrientation.h"


#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"




using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



FowardMovementSystem::FowardMovementSystem(void) : 
					BaseSystem("FowardMovementSystem")
{
	LOGTORS("************ FowardMovementSystem CTOR ************");	
}
	
FowardMovementSystem::~FowardMovementSystem(void) {
	LOGTORS("************ FowardMovementSystem DTOR ************");
}


void FowardMovementSystem::enter() {
	LOGINFO("[FowardMovementSystem::enter] FowardMovementSystem enter");	
	handleComponent("position");
	handleComponent("orientation");
	handleComponent("speed");	
	handleComponent("forward");	
}

void FowardMovementSystem::update(GameObject* go) {
	ComponentPosition* pos = 0;
	pos = static_cast<ComponentPosition*> (go->getComponent(POSITION));
	ComponentSpeed* pc = 0;
	pc = static_cast<ComponentSpeed*> (go->getComponent(SPEED));
	ComponentOrientation* ori = 0;
	ori = static_cast<ComponentOrientation*> (go->getComponent(ORIENTATION));

	//pos->position.z -=  pc->current_speed * World::getInstance()->getDelta() ;
	Vec3 deslocation = ori->orientation * Vec3(0,0,-pc->current_speed * World::getInstance()->getDelta());
	pos->position = pos->position + deslocation;
	
}

void FowardMovementSystem::exit() {
	LOGINFO("[FowardMovementSystem::exit] FowardMovementSystem exit");
}


/** WITH ORIENTATION
void FowardMovementSystem::update(GameObject* go) {
	ComponentPosition* pos = 0;
	pos = static_cast<ComponentPosition*> (go->getComponent(POSITION));
	ComponentSpeed* pc = 0;
	pc = static_cast<ComponentSpeed*> (go->getComponent(SPEED));
	ComponentOrientation* ori = 0;
	ori = static_cast<ComponentOrientation*> (go->getComponent(ORIENTATION));

	Vec3 deslocation = ori->orientation * Vec3(0,0,-pc->current_speed * World::getInstance()->getDelta());
	pos->position = pos->position + deslocation;
	
}
*/