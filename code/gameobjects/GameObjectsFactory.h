
/**
	factory rsponsable in create game objects from templates
		- inited by world
		- maps all templates for quick creation

*/


#ifndef __GOFACTORY_h_
#define __GOFACTORY_h_

#include "GameObjectCommon.h"

//#include <map>
#include <vector>



#include "../xml/rapidxml.hpp"
#include "../xml/rapidxml_print.hpp"
#include "../xml/rapidxml_utils.hpp"


namespace Venator {
	namespace GameObjectComponentSystem  {
		class GameObject;
		class Component;
		class GameObjectsFactory;
	}
}

class Venator::GameObjectComponentSystem::GameObjectsFactory {

	public:					
		void initialise(const std::string& templatefile);
		void destroy(void);
		void reset(void);

		GameObject* createGameObjectFromTemplate(const std::string& templatename);
		GameObject* createGameObjectFromTemplate(const std::string& templatename, const PARAMETERSMAP &params);
		
		friend class World;				

		static GameObjectsFactory& getSingleton(void);
		static GameObjectsFactory* getInstance( void );
	private:	
		GameObjectsFactory(void);
		~GameObjectsFactory(void);
		GameObjectsFactory( const GameObjectsFactory& ) { }
		GameObjectsFactory & operator = ( const GameObjectsFactory& );
		static GameObjectsFactory *mGameObjectsFactory;	

		void _populate(GameObject* o, const std::string& templatename);

		std::map<std::string, std::vector<std::string> > templates;
		
		/**
			for GO's template file
		*/
		rapidxml::xml_document<> doc;
		std::vector<char> buffer;

};	// class GameObjectsFactory



#endif
