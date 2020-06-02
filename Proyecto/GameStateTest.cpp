#include "GameStateTest.h"
#include "GameObjectTest.h"
#include "App.h"

GameStateTest::GameStateTest(){
    objects.push_back(new GameObjectTest(App::getInstance()->getRender(), 0, 0, 400, 400));
}
GameStateTest::~GameStateTest(){

}