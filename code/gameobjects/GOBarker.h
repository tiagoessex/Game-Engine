
/**

	notifies all systems (listeners) about any change in the world namely:
		- go add/removal
		- components add/removal
		- ...

	the world must inherit this class and implement the NotifyListeners method

	all listeners must inherit from GOListener and implement the receiveEvent method 


	notes:
		- it wortuld be much easier to just having the world directrly notify systemsmanager
		  and having it to perform ops
*/


#ifndef __GOObserver_H__
#define __GOObserver_H__

#include <set>

#include "GameObjectCommon.h"


namespace Venator {
	namespace GameObjectComponentSystem {
		class GOListener;
		class GameObject;
		class Component;
		class GOBarker;
	}
}
		
class Venator::GameObjectComponentSystem::GOBarker {
	private:
		std::set<GOListener*> listeners;

	public:
		void addListener(GOListener&);
		void removeListener(GOListener&);	
		void resetBarkerListeners(void);

		void emitEvent(GOSEVENTS, void*);

};	// class GOBarker


#endif
