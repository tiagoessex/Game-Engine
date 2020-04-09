


#include "GameObjectsRegistrations.h"
#include "ComponentsFactory.h"
#include "World.h"


#include "components/ComponentPosition.h"
#include "components/ComponentOrientation.h"
#include "components/ComponentScale.h"
#include "components/ComponentSpeed.h"
#include "components/ComponentForward.h"
#include "components/ComponentLifeSpan.h"
#include "components/ComponentPlayerShootLifetime.h"
#include "components/ComponentEnemyLifetime.h"
#include "components/ComponentCollisions.h"
#include "components/ComponentSound2D.h"
#include "components/ComponentSound3D.h"
#include "components/ComponentSoundListener.h"


// ogre direct dependency
#include "components/ComponentEntity.h"
#include "components/ComponentParticles.h"
#include "components/ComponentPlayerControl.h"
#include "components/ComponentRender.h"
#include "components/ComponentExplosion.h"
#include "components/ComponentSceneNodeAnimation.h"
#include "components/ComponentMeshAnimation.h"

// bullet direct dependency
#include "components/ComponentCollider.h"
#include "components/ComponentRigidBody.h"

#include "systems/PlayerControlSystem.h"
#include "systems/RenderPositionSystem.h"
#include "systems/FowardMovementSystem.h"
#include "systems/LifeSpanSystem.h"
#include "systems/PlayerShootLifetimeSystem.h"
#include "systems/EnemyLifetimeSystem.h"
#include "systems/MotionStateSystem.h"
#include "systems/CollisionsSystem.h"
#include "systems/ExplosionSystem.h"
#include "systems/SoundListenerSystem.h"
#include "systems/SceneNodeAnimationsSystem.h"
#include "systems/MeshAnimationsSystem.h"

using namespace Venator;
using namespace Venator::GameObjectComponentSystem;


void Venator::GameObjectComponentSystem::registerComponents(ComponentsFactory* cfactory) {
	cfactory->registerComponent("position",				POSITION,					&ComponentPosition::compFactory);
	cfactory->registerComponent("scale",				SCALE,						&ComponentScale::compFactory);
	cfactory->registerComponent("orientation",			ORIENTATION,				&ComponentOrientation::compFactory);	
	cfactory->registerComponent("speed",				SPEED,						&ComponentSpeed::compFactory);
	cfactory->registerComponent("forward",				FORWARD,					&ComponentForward::compFactory);
	cfactory->registerComponent("lifespan",				LIFESPAN,					&ComponentLifeSpan::compFactory);
	cfactory->registerComponent("playershootlifetime",	PLAYERSHOOTLIFETIME,		&ComponentPlayerShootLifetime::compFactory);
	cfactory->registerComponent("enemylifetime",		ENEMYLIFETIME,				&ComponentEnemyLifetime::compFactory);
	cfactory->registerComponent("collisions",			COLLISIONS,					&ComponentCollisions::compFactory);
	cfactory->registerComponent("sound2d",				SOUND2D,					&ComponentSound2D::compFactory);
	cfactory->registerComponent("sound3d",				SOUND3D,					&ComponentSound3D::compFactory);
	cfactory->registerComponent("soundlistener",		SOUNDLISTENER,				&ComponentSoundListener::compFactory);
		
	// ogre direct dependency
	cfactory->registerComponent("entity",				ENTITY,						&ComponentEntity::compFactory);
	cfactory->registerComponent("particles",			PARTICLES,					&ComponentParticles::compFactory);
	cfactory->registerComponent("playercontrol",		PLAYERCONTROL,				&ComponentPlayerControl::compFactory);
	cfactory->registerComponent("render",				RENDER,						&ComponentRender::compFactory);
	cfactory->registerComponent("explosion",			EXPLOSION,					&ComponentExplosion::compFactory);
	cfactory->registerComponent("scenenodeanimation",	SCENENODEANIMATION,			&ComponentSceneNodeAnimation::compFactory);
	cfactory->registerComponent("meshanimation",		MESHANIMATION,				&ComponentMeshAnimation::compFactory);
	
	

	// bullet direct dependency
	cfactory->registerComponent("rigidbody",			RIGIDBODY,					&ComponentRigidBody::compFactory);
	cfactory->registerComponent("collider",				COLLIDER,					&ComponentCollider::compFactory);
}

void Venator::GameObjectComponentSystem::registerSystems(World* world) {
	world->addSystem(new RenderPositionSystem());
	world->addSystem(new PlayerControlSystem());
	world->addSystem(new FowardMovementSystem());
	world->addSystem(new LifeSpanSystem());
	world->addSystem(new PlayerShootLifetimeSystem());
	world->addSystem(new EnemyLifetimeSystem());
	world->addSystem(new MotionStateSystem());
	world->addSystem(new CollisionsSystem());
	world->addSystem(new ExplosionSystem());
	world->addSystem(new SoundListenerSystem());
	world->addSystem(new SceneNodeAnimationsSystem());
	world->addSystem(new MeshAnimationsSystem());
}