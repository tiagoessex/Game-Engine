

#include "EventsManager.h"
#include "Listener.h"

#include <iostream>


using namespace Venator::Events;


EventsDispacher* EventsDispacher::mEventsDispacher = 0;

 void EventsDispacher::registerListener(Listener& l, const EVENTS& ev) {
     EVENTSMAP::iterator it;
     it = eventsMap.find(ev);
     if (it == eventsMap.end()) {
        std::set<Listener*> temp;
        temp.insert(&l);
        eventsMap[ev] = temp;
        std::cout<<"new event type > "<<ev<<" added"<<std::endl;

        std::cout<<"current event listener size > "<<temp.size()<<std::endl;
     } else {
        (*it).second.insert(&l);
        std::cout<<"current event listener size > "<<(*it).second.size()<<std::endl;
     }
 }

 void EventsDispacher::unRegisterListener(const Listener& l) {
     for (EVENTSMAP::iterator it=eventsMap.begin(); it!=eventsMap.end(); ++it) {
         for (std::set<Listener*>::iterator it2=(*it).second.begin(); it2!=(*it).second.end(); ++it2) {
            if ((*it2) == &l) {
                //std::cout<<"foudned"<<std::endl;
                (*it).second.erase(it2);
                break;
            }
         }
     }
 }

 void EventsDispacher::unRegisterEventFromListener(Listener& l, const EVENTS& ev) {
     EVENTSMAP::iterator it;
     it = eventsMap.find(ev);
     if (it != eventsMap.end()) {
        std::set<Listener*>::iterator it2 = (*it).second.find(&l);
        if (it2 != (*it).second.end()) {
            (*it).second.erase(it2);
        }
     }
 }

 void EventsDispacher::emitEvent(const EVENTS& ev, void* params) {
     std::map< EVENTS,std::set<Listener*> >::iterator it;
     it = eventsMap.find(ev);
     if (it != eventsMap.end()) {
         for (std::set<Listener*>::iterator it2=(*it).second.begin(); it2!=(*it).second.end(); ++it2) {
            (*it2)->receiveEvent(ev, params);
         }
     }
 }

void EventsDispacher::reset(void) {
    for (EVENTSMAP::iterator it=eventsMap.begin(); it!=eventsMap.end(); ++it) {
        (*it).second.clear();
     }
     eventsMap.clear();
}

EventsDispacher* EventsDispacher::getInstance( ) {
    if (!mEventsDispacher) {
            mEventsDispacher = new EventsDispacher();
    }
    return mEventsDispacher;
}
