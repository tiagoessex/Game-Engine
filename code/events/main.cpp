#include <iostream>
#include <set>

#include "Listener.h"
#include "EventsManager.h"

using namespace std;

using namespace Venator::Events;

class C1 : public Listener {
    void receiveEvent(EVENTS ev, Event* info) {
        cout<<"C1 event "<<ev<<" reveived"<<endl;
        switch (info->id) {
            case EVENT_1: {
                Event1* e = static_cast<Event1*> (info);
                cout<<"params > "<<e->a<<" | " <<e->b<<endl;
            }
                break;
            case EVENT_2: {
                Event2* e = static_cast<Event2*> (info);
                cout<<"params > "<<e->a<<" | " <<e->b<<endl;
            }
                break;
            default: break;
        }
    };
};


int main()
{
    C1 c1;
    C1 c3,c4,c5;
    C1* c = new C1;
    EventsDispacher::getInstance()->registerListener(c1,EVENT_1);
    EventsDispacher::getInstance()->registerListener(*c,EVENT_1);
    EventsDispacher::getInstance()->registerListener(c1,EVENT_2);
    cout<<"sending event_1"<<endl;


    Event1 qwe;
    qwe.id = EVENT_1;
    qwe.a = 10;
    qwe.b = 200;

    Event2 qwe2;
    qwe2.id = EVENT_2;
    qwe2.a = 10;
    qwe2.b = 'a';

    //EventsDispacher::getInstance()->emitEvent(EVENT_2, (void*) (&qwe2));
    cout<<"-------------"<<endl;
    EventsDispacher::getInstance()->emitEvent(EVENT_2, &qwe2);
    cout<<"-------------"<<endl;
    EventsDispacher::getInstance()->emitEvent(EVENT_1, &qwe);

    return 0;
}
