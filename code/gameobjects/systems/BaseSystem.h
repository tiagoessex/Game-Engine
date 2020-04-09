

/**
	
	systems types:
		update(GameObject* go) => handles more than 1 component
		update(Component* c)  => handles only 1 component
		update(const std::vector<GameObject*>& gos) => handles more than 1 component
			not very different from update(GameObject* go) the processing loop (if there is one) 
			is inside this update function 
*/

#ifndef __BaseSystem_H__
#define __BaseSystem_H__

#include <vector>
#include <string>

#include "../GameObjectCommon.h"
#include "../GOListener.h"
#include "../../Prerequisites.h"

namespace Venator {
	namespace GameObjectComponentSystem {
		class Component;
		class GameObject;
		class BaseSystem;
	}
}


class Venator::GameObjectComponentSystem::BaseSystem : public GOListener {
	public:		
		// use string just to be easy to debug and develop
		// remove it when everything done
		// all => will only call Update() - general update
		// deltatime indicates the delta interval to preoceed with the system's update
		BaseSystem(const std::string& name, bool all = false, Scalar deltatime = 0);
		virtual ~BaseSystem(void);
		void setEnable(bool e) { enabled = e; };
		bool isEnable(void) const { return enabled; };
		bool isAll(void) { return all; };
		
		void clear(void);		// remove all gos and components
		//void Refresh(void);

		// thse funcs will be called during creation/destruction of the system and
		// world's update - user defined
		// how objects and component should be updated - user defined

		// how each go/component or the entire collection should be updated
		// ATT: only one of these should be implemented depending on the system
		// ATT: imp only one of these
		virtual void update(GameObject* go) {};	// each go - called by _updateSystem
		virtual void update(Component* c) {};	// each comp used only when system handles only 1 component 
										// and all flag is false - called by _updateSystem
		virtual void update(const std::vector<GameObject*>& gos) {};	// all gos - called by _updateSystem (all flag = true)
		

		virtual void enter() {};				// called by systemsmanager during system init
		virtual void updateStart() {};			// called by systemsmanager during update	
		virtual void updateEnd() {};			// called by systemsmanager during update
		virtual void exit() {};					// called by systemsmanager during system finalizing
			

		// set = true => handle component else don't handle component
		// usefull if the system decides not to update that component
		// ATT: the collection selection is done during init => it won't switch
		// from entities to component if only 1 component remains to be handled
		void handleComponent(const std::string& componentName, bool set = true);
		void handleComponent(const CPOS& componentID, bool set = true);
		const BITSET& getComponentBits() { return bitfield; }

		// system's name
		const std::string& getName(void) { return name; };

		// events dealer
		void receiveEvent(GOSEVENTS ev, void* info);

		friend class SystemsManager;	// to allow access to _updateSystem()
		/** used 3 times in each update loop
			=> public => inc perf. 
		*/
		bool updatable;		

	private:
		BITSET bitfield;	// bitfield indicating all compoents the go has
		bool enabled;
		std::string name;
		

		// events receivers - ATT: it would be much cheaper if
		//					  all checks were implemented in manager
		void _addGameObject(GameObject* go);
		void _removeGameObject(GameObject* go);
		void _addComponent(Component* c);
		void _removeComponent(Component* c);
		
		// update collections - the update functions used will be user defined
		// called by systemsmanager - the update function that this func will call
		// depends on which update is implemented <= which collection is components or gos
		void _updateSystem(void);

		std::vector<Component*> components;
		std::vector<GameObject*> gos;
		bool all;	// general update
		Scalar deltatime, currentime;
	//	World* world;

};		// class BaseSystem




#endif

