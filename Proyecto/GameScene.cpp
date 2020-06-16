#include "GameScene.h"
#include "PhysicsObject.h"
#include "Fighter.h"

GameScene::GameScene(App* ap): GameState(ap){
}

void GameScene::start(){
    objects.push_back(new PhysicsObject(app, 320, 420, 680, 75, "koji.jpeg", STATIC, 1, 1, 0, 0, false));
    objects.back()->setTag("Ground");
    objects.push_back(new Fighter(app, 320, 100, 200, 200, "FatalFurry_sprite.png", DYNAMIC, 0.15f, 0.4f, -5, 25, true));
    objects.back()->setTag("Fighter1");
}