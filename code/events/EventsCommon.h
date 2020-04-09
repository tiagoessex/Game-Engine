
#ifndef _EVENTSCOMMON_H_
#define _EVENTSCOMMON_H_

namespace Venator {
	namespace GameObjectComponentSystem {
		class GameObject;
	}
}

namespace Venator {
    namespace Events {

        enum EVENTS {	PLAYER_SHOOT, 
						COLLISIONHIT, 
						PLAYER_DIE 
					};

        struct Event {};

        struct HitInfo : Event {
            Venator::GameObjectComponentSystem::GameObject* object1;
            Venator::GameObjectComponentSystem::GameObject* object2;
        };

        struct Event2 : Event {
            int a;
            char b;
        };

    }
}

#endif
