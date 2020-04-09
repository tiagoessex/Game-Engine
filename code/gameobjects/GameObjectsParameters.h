
/**
	template parameters

	inited by world

*/


#ifndef __GameObjectsParameters_h_
#define __GameObjectsParameters_h_



#include <map>
#include <vector>

#include "GameObjectCommon.h"

#include "../xml/rapidxml.hpp"
#include "../xml/rapidxml_print.hpp"
#include "../xml/rapidxml_utils.hpp"


namespace Venator {
	namespace GameObjectComponentSystem	{
		class GameObjectsParameters;
	}
}

class Venator::GameObjectComponentSystem::GameObjectsParameters {



	public:
		void initialise(const char* templatefile);
		void destroy(void);
		void reset(void);

        PARAMETERSMAP getParameters(const std::string& name);

		static GameObjectsParameters& getSingleton(void);
		static GameObjectsParameters* getInstance( void );
	private:
		GameObjectsParameters(void);
		~GameObjectsParameters(void);
		GameObjectsParameters( const GameObjectsParameters& ) { }
		GameObjectsParameters & operator = ( const GameObjectsParameters& );
		static GameObjectsParameters *mGameObjectsParameters;

		// go class name | params map
        std::map<std::string, PARAMETERSMAP > templates;
		PARAMETERSMAP empty;

		rapidxml::xml_document<> doc;
		std::vector<char> buffer;

};	// class GameObjectsFactory



#endif
