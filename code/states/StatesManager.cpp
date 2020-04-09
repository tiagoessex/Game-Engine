



// Venator headers
#include "StatesManager.h"
#include "GameState.h"


using namespace Venator;
using namespace Venator::GameStates;


StatesManager *StatesManager::mStatesManager = 0;

StatesManager::StatesManager(void)
{}

StatesManager::~StatesManager(void) 
{}

bool StatesManager::initialise(void) 
{
	return true;
}

void StatesManager::destroy(void) 
{
	reset();
	delete mStatesManager;	
}


void StatesManager::changeState(GameState* state) {
	// cleanup the current state
	if ( !states.empty() )  {
		GameState* st = states.back();
		st->onEXIT();
		delete st;
		st = 0;
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->onENTER();

}

void StatesManager::pushState(GameState* state) {
	// pause current state
	if ( !states.empty() ) {
		states.back()->onPAUSE();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->onENTER();
}

void StatesManager::popState(void) {
    // cleanup the current state
    if ( !states.empty() ) {
		GameState* st = states.back();
		st->onEXIT();
		delete st;			
		st = 0;
		states.pop_back();
    }
 
    // resume previous state
    if ( !states.empty() ) {
        states.back()->onRESUME();
    }
}

GameState* StatesManager::getCurrentState(void) {
	if (!states.empty()) {
		return states.back();
	}
	return 0;
}

void StatesManager::reset(void) {
	// clear any remaining states
	GameState* ent;
	while(!states.empty()) {		
		ent = states.back();	
		ent->onEXIT();
		delete ent;	
		ent=0;
		states.pop_back();		
	}	
	states.clear();
}

StatesManager& StatesManager::getSingleton(void) {  
    assert(mStatesManager);
    return *mStatesManager;
}


StatesManager* StatesManager::getInstance( void ) {
	if( !mStatesManager ) {
        mStatesManager = new StatesManager();
    }
    return mStatesManager;
}