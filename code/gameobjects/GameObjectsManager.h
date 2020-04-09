

/**
	manages the active go collection

*/


#ifndef __GameObjectsManager_h_
#define __GameObjectsManager_h_

#include <vector>

#include "GameObjectCommon.h"

namespace Venator {
	namespace GameObjectComponentSystem	{
		class GameObject;
		class GameObjectsManager;
	}
}

class Venator::GameObjectComponentSystem::GameObjectsManager {
	public:					
		void initialise(void);
		void destroy(void);
		void reset(void);		// eliminates all gos - call dtor
		void clear(void);		// = reset()

		void addGameObject(GameObject* go);
		bool removeGameObject(GameObject* go);	// just remove from collection
		bool removeGameObject(const LLG& goid);	// just remove from collection
		bool deleteGameObject(GameObject* go);	// remove + delete
		bool deleteGameObject(const LLG& goid);	// remove + delete

		bool hasGameObject(GameObject* go);

		GameObject* getGameObject(const LLG& goid);
		const std::vector<GameObject*>& getEntities(void) { return gos; };

		

		static GameObjectsManager* getInstance( void );
		static GameObjectsManager& getSingleton(void);
	private:	
		GameObjectsManager(void);
		~GameObjectsManager(void);
		GameObjectsManager( const GameObjectsManager& ) { }
		GameObjectsManager & operator = ( const GameObjectsManager& );

		std::vector<GameObject*> gos;

		static GameObjectsManager *mGameObjectsManager;	

};	// class GameObjectsManager



#endif
