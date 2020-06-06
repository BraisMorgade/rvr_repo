#include "GameScene.h"
#include "PhysicsObject.h"

GameScene::GameScene(App* ap): GameState(ap){
    objects.push_back(new PhysicsObject(app, 200, 200, 150, 150, "koji.jpeg"));
}