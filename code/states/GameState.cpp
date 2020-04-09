

#include "GameState.h"

// Venator headers
#include "StatesManager.h"

using namespace Venator::GameStates;

int GameState::ID = 0;

GameState::GameState(void) : id(ID) {
	ID++;
}

void GameState::changeState(GameState* state) { 
	StatesManager::getInstance()->changeState(state); 
}

void GameState::pushState(GameState* state) { 
	StatesManager::getInstance()->pushState(state); 
}

void GameState::popState() { 
	StatesManager::getInstance()->popState();
}
		