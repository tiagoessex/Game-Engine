

#include "GOBarker.h"
#include "GOListener.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;



void GOBarker::addListener(GOListener& o) {
    listeners.insert(&o);
}

void GOBarker::removeListener(GOListener& o) {
    listeners.erase(&o);
}

void GOBarker::emitEvent(GOSEVENTS ev, void* info) {
    for (std::set<GOListener*>::iterator itr = listeners.begin(); itr != listeners.end(); itr++ ) {
		(*itr)->receiveEvent(ev, info);
	}
}


void GOBarker::resetBarkerListeners(void) {
	listeners.clear();
}

