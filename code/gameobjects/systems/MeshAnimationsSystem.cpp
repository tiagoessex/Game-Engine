

#include "MeshAnimationsSystem.h"
#include "../GameObject.h"
#include "../components/ComponentMeshAnimation.h"
#include "../World.h"

#include "../../Globals.h"
#include "../../utils/VenatorUtils.h"


#include "OgreAnimationState.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



MeshAnimationsSystem::MeshAnimationsSystem(void) : 
			BaseSystem("MeshAnimationsSystem")
{
	LOGTORS("************ MeshAnimationsSystem CTOR ************");	
}
	
MeshAnimationsSystem::~MeshAnimationsSystem(void) {
	LOGTORS("************ MeshAnimationsSystem DTOR ************");
}


void MeshAnimationsSystem::enter() {
	LOGINFO("[MeshAnimationsSystem::enter] MeshAnimationsSystem enter");	
	handleComponent("meshanimation");
}

void MeshAnimationsSystem::update(Component* c) {
	ComponentMeshAnimation* animation = 0;
	animation = static_cast<ComponentMeshAnimation*> (c);	

	if (animation->getAnimationState()) {
		animation->getAnimationState()->addTime(World::getInstance()->getDelta());
	}		
}



void MeshAnimationsSystem::exit() {
	LOGINFO("[MeshAnimationsSystem::exit] MeshAnimationsSystem exit");
}
