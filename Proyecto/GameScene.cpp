#include "GameScene.h"
#include "PhysicsObject.h"
#include "Fighter.h"
#include "App.h"
#include "NetMessage.h"

GameScene::GameScene(App* ap): GameState(ap){
}

void GameScene::start(){
    objects.push_back(new PhysicsObject(app, 320, 420, 680, 75, "koji.jpeg", STATIC, 1, 1, 0, 0, false));
    objects.back()->setTag("Ground");

    Fighter* f1=new Fighter(app, 200, 100, 200, 200, "FatalFurry_sprite.png", DYNAMIC, 0.15f, 0.4f, -5, 25, false, app->getPlayer()==1);
    f1->setTag("Fighter1");
    Fighter* f2=new Fighter(app, 400, 100, 200, 200, "FatalFurry_sprite.png", DYNAMIC, 0.15f, 0.4f, -5, 25, false, app->getPlayer()==2);
    f2->setTag("Fighter2");
    objects.push_back(f1);
    objects.push_back(f2);

    if(app->getPlayer()==1){
        localFg=f1;
        remoteFg=f2;
    }
    else{
        localFg=f2;
        remoteFg=f1;
    }

}

void GameScene::send(){
    if(localFg!=nullptr){
        localFg->to_bin();
        NetMessage m(NetMessage::INPUT, localFg->data());
        app->getSocket()->send(m, *app->getSocket());
    }
}

void GameScene::receive(){
    if(remoteFg!=nullptr){
        NetMessage m;
        Socket* opEnd;
        app->getSocket()->recv(m, opEnd);
        if(m.type==NetMessage::INPUT){
            remoteFg->from_bin(m.message);
        }
    }
}