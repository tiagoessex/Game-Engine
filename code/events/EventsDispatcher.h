
#ifndef _EventsDispacher_H_
#define _EventsDispacher_H_

#include <map>
#include <set>

#include "EventsCommon.h"


namespace Venator {
    namespace Events {
        class Listener;
        class EventsDispatcher;
    }
}


class Venator::Events::EventsDispatcher {
    typedef std::map< int,std::set<Listener*> > EVENTSMAP;
    EVENTSMAP eventsMap;

    public:
        ~EventsDispatcher() {};
		void initialise(void) {};
		void destroy(void);		

        void registerListener(Listener&, EVENTS);
        void unRegisterListener(const Listener&);
        void unRegisterEventFromListener(Listener&, EVENTS);
        void emitEvent(EVENTS, Event* params=0);
        void reset(void);

        static EventsDispatcher* getInstance( );

    private:
        EventsDispatcher() {};
        EventsDispatcher(EventsDispatcher const&);
        void operator=(EventsDispatcher const&);
        static EventsDispatcher* mEventsDispacher;

};

#endif
