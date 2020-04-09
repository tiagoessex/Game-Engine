

#ifndef __StatesManager_h_
#define __StatesManager_h_


#include <vector>

namespace Venator {	
	namespace GameStates {
		class GameState;
		class StatesManager;
	}
}

class Venator::GameStates::StatesManager {
	public:		
		bool initialise(void);
		void destroy(void);
		void reset(void);
		
		void changeState(GameStates::GameState* state);
		void pushState(GameStates::GameState* state);
		void popState(void);
		GameState* getCurrentState(void);

		static StatesManager* getInstance(void);
		static StatesManager& getSingleton(void);
	private:
		StatesManager(void);
		virtual ~StatesManager(void);
		StatesManager( const StatesManager& ) { }
		StatesManager & operator = ( const StatesManager& );
		static StatesManager *mStatesManager;

		std::vector<GameState*> states;


};		// class StatesManager


#endif
