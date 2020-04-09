


#ifndef __GOListener_H__
#define __GOListener_H__


#include "GameObjectCommon.h"

namespace Venator {
	namespace GameObjectComponentSystem {
		class GameObject;
		class Component;
		class GOListener;
	}
}

class Venator::GameObjectComponentSystem::GOListener {
	public:
		virtual void receiveEvent(GOSEVENTS ev, void* info) = 0;

};	// class GOListener


#endif
