

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
        virtual void receiveEvent(EVENTS ev, Event* info = 0) = 0;
};


#endif
