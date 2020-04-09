

/**
	on shoot emits signal:	
		sigc::signal<void, Vec3&, Vec3&, Ogre::SceneManager*> shoot;	

	connected to:
		Venator::Actions::playerShoot
*/


#ifndef __PlayerControlSystem_H__
#define __PlayerControlSystem_H__


#include "BaseSystem.h"
#include "../../Prerequisites.h"

//#include "sigc++/sigc++.h"

namespace Venator {
	namespace InputEngine {
		class InputManager;
	}

	namespace GameObjectComponentSystem	{
		class PlayerControlSystem;
	}
}

namespace Ogre {
	class SceneManager;
}


class Venator::GameObjectComponentSystem::PlayerControlSystem : public BaseSystem	//, public EventsDispatcher
{
	public:		
		PlayerControlSystem(void);
		~PlayerControlSystem(void);			

		void update(GameObject* c);		// each go - called by _updateSystem
		void enter();					// called by systemsmanager during system init
		void exit();					// called by systemsmanager during system finalizing
			
	private:
		InputEngine::InputManager* input_manager;

		void _shoot(Vec3& position);

	//	sigc::signal<void, Vec3&> shoot;
	//	sigc::connection c;

};


#endif