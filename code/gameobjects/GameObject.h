
/**
	game object or entity

		each entity should only hold:
			- unique id
			- bitfield representing all components it has
			- components container
			- get / set

	ATT:
		- go should be created/destroyed through world
		- components are eliminated by ComponentsFactory

*/

#ifndef __GameObject_H__
#define __GameObject_H__

#include <map>
#include <string>

#include "GameObjectCommon.h"



namespace Venator {
	namespace GameObjectComponentSystem	{
		class Component;
		class GameObject;
	}
}
class Venator::GameObjectComponentSystem::GameObject {

	public:					
		Component* getComponent(const CPOS& type);			
		Component* getComponent(const std::string& name);
		bool hasComponent(const CPOS& id);
		bool hasComponent(const std::string& name);
					
		const LLG& getID(void) const { return id; };	

		const BITSET& getBitField() { return bitfield; }

		void setEnable(bool e) { enabled = e; };
		bool isEnable(void) const { return enabled; };

		PARAMETERSMAP parameters;

		friend class World;
		friend class GameObjectsManager;
		friend class GameObjectsFactory;

	protected:
		GameObject(void);
		GameObject(const PARAMETERSMAP& parameters);
		~GameObject(void);
		bool addComponent(Component* NewComponent);
		bool deleteComponent(const CPOS& id);
		bool deleteComponent(Component* c);		
		
	private:
		std::map<CPOS, Component*> components;
		
		LLG id;							// unique GO number id									
		BITSET bitfield;				// bitfield representing all compoents the go has
		bool enabled;					// set to be operated on by the systems

		static LLG ID;					// each time a new GO is created, ID++


};		// class gameobject


#endif
