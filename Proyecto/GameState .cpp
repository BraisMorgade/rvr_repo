#include "GameState.h"

GameState::GameState(){

}
GameState::~GameState(){

}
void GameState::start(){
    for(auto o: objects){
        (*o).start();
    }
}
void GameState::update(){
    for(auto o: objects){
        (*o).update();
    }
}
void GameState::render(SDL_Renderer* render){
    for(auto o: objects){
        (*o).render();
    }
    SDL_RenderPresent(render);
}
void GameState::handleInput(SDL_Event& event){
    for(auto o: objects){
        (*o).handleInput();
    }
}
void GameState::end(){
    
}