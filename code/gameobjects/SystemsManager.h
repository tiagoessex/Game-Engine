
/**
	just to hold and manage all systems

	notes:
		- differentiating updatable and non updatabled to easy and reduze overhead
		- spite the differentiation, the upt and non-upd have the same base class, however
		  the overhead fall only in mem and not in the exec

	to do:
		- differentiate both upt/non-upd bases with templates

*/


#ifndef __SystemsManager_h_
#define __SystemsManager_h_


#include <boost/dynamic_bitset.hpp>

#include "GameObjectCommon.h"

namespace Venator {
	namespace GameObjectComponentSystem {
		class GameObject;
		class Component;
		class BaseSystem;
		class SystemsManager;
	}
}

class Venator::GameObjectComponentSystem::SystemsManager {
	public:					
		void initialise(void);
		void destroy(void);
		void reset(void);					
		void clear(void);

		void updateStart(void);
		void update(void);
		void updateEnd(void);

		std::string _debugPrint(void);

		friend class World;

		static SystemsManager* getInstance( void );
		static SystemsManager& getSingleton(void);
	private:	
		SystemsManager(void);
		~SystemsManager(void);
		SystemsManager( const SystemsManager& ) { }
		SystemsManager & operator = ( const SystemsManager& );
		static SystemsManager *mSystemsManager;	

		// when new system added => set system's collections 
		// after that all ops on the collections are done by the
		// system itself by receiving signals from the world
		void _addSystem(BaseSystem* system, const std::vector<GameObject*>& gos);//, bool updatable);
		bool _deleteSystem(BaseSystem* system);
		
		BaseSystem* _getSystem(const std::string& systemName);
		bool _hasSystem(const std::string& systemName);


		std::vector<BaseSystem*> systems;
		//std::vector<BaseSystem*> non_updatable_systems;

};


#endif
