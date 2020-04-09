

#ifndef _Listener_H_
#define _Listener_H_



#include "EventsCommon.h"

namespace Venator {
    namespace Events {
        class Listener;
    }
}

class Venator::Events::Listener {
    public:
        virtual void receiveEvent(const EVENTS& ev, void* info) = 0;
};


#endif
