#include "GameStateMachine.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "App.h"

GameStateMachine::GameStateMachine(App* ap){
    app=ap;

    GameState* menu= new MainMenu(app);
    GameState* game= new GameScene(app);

    states.emplace("menu", menu);
    states.emplace("game", game);

    currentState=menu;
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
