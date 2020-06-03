#include "GameStateTest.h"
#include "GameObjectTest.h"
#include "App.h"

GameStateTest::GameStateTest(App* ap): GameState(ap){
    GameObject* aux = new GameObjectTest(app->getRender(), 0, 0, 400, 400);
    objects.push_back(aux);
}
GameStateTest::~GameStateTest(){

}

void GameStateTest::render(SDL_Renderer* render){
    objects.back()->render();
    SDL_RenderPresent(render);
}
