#include "GameStateMachine.h"
#include "GameStateTest.h"


GameStateMachine* GameStateMachine::instance=0;

GameStateMachine::GameStateMachine(){
    states["test"]= new GameStateTest();
}

GameStateMachine* GameStateMachine::getInstance()
{
    if(instance==nullptr){
        instance= new GameStateMachine();
    }
    return instance;
}

GameStateMachine::~GameStateMachine(){

}

void GameStateMachine::changeState(std::string state){
    currentState->end();
    currentState=states[state];
    currentState->start();
}

GameState* GameStateMachine::getCurrentState(){
    return currentState;
}