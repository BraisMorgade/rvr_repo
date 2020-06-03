#include "GameStateMachine.h"
#include "GameStateTest.h"
#include "App.h"

GameStateMachine::GameStateMachine(App* ap){
    app=ap;
    GameState* aux= new GameStateTest(ap);
    states.emplace("test", aux);
    currentState=aux;
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
