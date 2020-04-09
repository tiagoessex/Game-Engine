
#ifndef _EventsDispacher_H_
#define _EventsDispacher_H_

#include <map>
#include <set>

#include "EventsCommon.h"


namespace Venator {
    namespace Events {
        class Listener;
        class EventsDispacher;
    }
}


class Venator::Events::EventsDispacher {
    typedef std::map< EVENTS,std::set<Listener*> > EVENTSMAP;
    EVENTSMAP eventsMap;

    public:
        ~EventsDispacher() {};

        void registerListener(Listener&, const EVENTS&);
        void unRegisterListener(const Listener&);
        void unRegisterEventFromListener(Listener&, const EVENTS&);
        void emitEvent(const EVENTS&, void* params=0);
        void reset(void);

        static EventsDispacher* getInstance( );

    private:
        EventsDispacher() {};
        EventsDispacher(EventsDispacher const&);
        void operator=(EventsDispacher const&);
        static EventsDispacher* mEventsDispacher;

};

#endif
