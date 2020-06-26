#include "MainMenu.h"
#include "CreateButton.h"
#include "JoinButton.h"
#include "NetMessage.h"
#include "App.h"
#include "GameStateMachine.h"

MainMenu::MainMenu(App* ap):GameState(ap){
}

void MainMenu::start(){
    objects.push_back(new CreateButton(app, 320, 140, 200, 100, "BotonCrear.png"));
    objects.push_back(new JoinButton(app, 320, 340, 200, 100, "BotonUnirse.png"));
    joining=false;
    creating=false;
}

void MainMenu::send(){
    NetMessage m;
    if(joining){
        m.type = NetMessage::JOIN;
        app->getSocket()->send(m, *app->getSocket());
        joining=false;
    }
    else if(creating){
        m.type = NetMessage::CREATE_ROOM;
        app->getSocket()->send(m, *app->getSocket());
        creating=false;
    }
}

void MainMenu::receive(){
    NetMessage m;
    app->getSocket()->recv(m);
    switch(m.type){
        case NetMessage::CREATE_ROOM:
            std::cout<<"created"<<std::endl;
            break;
        case NetMessage::JOIN:
            if(joining)
                std::cout<<"joinedRoom"<<std::endl;
            else
                std::cout<<"playerJoinedTheRoom"<<std::endl;
            if(joining) joining=false;
            if(creating) creating=false;
            app->getStateMachine()->changeState("game");
            break;
        default:
            break;
    }
}