#include "GameScene.h"
#include "PhysicsObject.h"
#include "Fighter.h"

GameScene::GameScene(App* ap): GameState(ap){
    objects.push_back(new PhysicsObject(app, 200, 325, 250, 75, "koji.jpeg", STATIC));
    objects.push_back(new Fighter(app, 150, 100, 100, 100, "koji.jpeg", DYNAMIC));
}