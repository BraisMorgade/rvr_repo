#include "GameState.h"
#include "App.h"

GameState::GameState(App* ap){
    app=ap;
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
    SDL_RenderClear(render);
    for(auto o: objects){
        (*o).render();
    }
    SDL_RenderPresent(render);
}
void GameState::handleInput(SDL_Event& event){
    for(auto o: objects){
        (*o).handleInput(event);
    }
}
void GameState::end(){
    for(auto o:objects){
        (*o).readyToDestroy(true);
    }
}

void GameState::destroyReadyEntities(){
    auto ind=objects.begin();
    while(ind!=objects.end()){
        auto aux = ind;
        aux++;
        if((*ind)->isReadyToDestroy()){
            delete *ind;
            objects.erase(ind);
        }
        ind=aux;
    }
}