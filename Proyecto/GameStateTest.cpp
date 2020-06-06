#include "GameStateTest.h"
#include "PhysicsObject.h"
#include "App.h"

GameStateTest::GameStateTest(App* ap): GameState(ap){
    GameObject* aux = new PhysicsObject(app, 0, 0, 400, 400, "koji.jpeg");
    objects.push_back(aux);
}
GameStateTest::~GameStateTest(){

}
