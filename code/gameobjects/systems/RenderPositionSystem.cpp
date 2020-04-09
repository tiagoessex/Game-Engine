

#include "RenderPositionSystem.h"
#include "../GameObject.h"
#include "../components/ComponentRender.h"
#include "../components/ComponentPosition.h"

#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



RenderPositionSystem::RenderPositionSystem(void) : BaseSystem("RenderPositionSystem")
{
	LOGTORS("************ RenderPositionSystem CTOR ************");	
}
	
RenderPositionSystem::~RenderPositionSystem(void) {
	LOGTORS("************ RenderPositionSystem DTOR ************");
}


void RenderPositionSystem::enter() {
	LOGINFO("[RenderPositionSystem::enter] RenderPositionSystem enter");	
	handleComponent("render");
	handleComponent("position");	
	handleComponent("speed");	
//	handleComponent("playercontrol");

}

void RenderPositionSystem::update(GameObject* go) {
	ComponentRender* render = 0;
	render = static_cast<ComponentRender*> (go->getComponent(RENDER));
	ComponentPosition* pos = 0;
	pos = static_cast<ComponentPosition*> (go->getComponent(POSITION));

	if (render && pos && render->getSceneNode()) {
		render->getSceneNode()->setPosition(pos->getPosition());
	}
	//LOGINFO(("RenderPositionSystem UPODADTIN GO > " + Venator::Utils::Number2String(go->getID())).c_str());
}

void RenderPositionSystem::exit() {
	LOGINFO("[RenderPositionSystem::exit] RenderPositionSystem exit");
}
