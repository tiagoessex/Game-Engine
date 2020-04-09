
#ifndef _EVENTSCOMMON_H_
#define _EVENTSCOMMON_H_

#include <string>

namespace Venator {
    namespace Events {

        //enum EVENTS { EVENT_1, EVENT_2, EVENT_3, EVENT_4 };
        typedef std::string EVENTS;


        struct Event {
            size_t sender;
        };

        struct Event_1 {
        };

    }
}


//// apagar

struct ST {
    int a;
    int b;
};
//


#endif
