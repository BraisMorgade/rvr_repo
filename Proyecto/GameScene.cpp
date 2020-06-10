#include "GameScene.h"
#include "PhysicsObject.h"
#include "Fighter.h"

GameScene::GameScene(App* ap): GameState(ap){
}

void GameScene::start(){
    objects.push_back(new PhysicsObject(app, 320, 420, 680, 75, "koji.jpeg", STATIC));
    objects.push_back(new Fighter(app, 320, 100, 100, 100, "koji.jpeg", DYNAMIC));
}