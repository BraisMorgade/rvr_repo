#include "GameStateTest.h"
#include "GameObjectTest.h"
#include "App.h"

GameStateTest::GameStateTest(App* ap): GameState(ap){
    GameObject* aux = new GameObjectTest(app, 0, 0, 400, 400);
    objects.push_back(aux);
}
GameStateTest::~GameStateTest(){

}
