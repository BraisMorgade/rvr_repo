#include "Fighter.h"

Fighter::Fighter(App* ap, int posx, int posy, int w, int h, std::string image, BodyType type)
:PhysicsObject(ap, posx, posy, w, h, image, type){
    in.left=false;
    in.right=false;
    in.up=false;
    in.down=false;
}

void Fighter::update(){
    PhysicsObject::update();
    if(in.up){
        body->SetLinearVelocity(b2Vec2(0, -1));
    }
    else if(in.right){
        body->SetLinearVelocity(b2Vec2(1,0));
    }
    else if(in.left){
        body->SetLinearVelocity(b2Vec2(-1,0));
    }
    else{
        body->SetLinearVelocity(b2Vec2(0,body->GetLinearVelocity().y));
    }
}

void Fighter::handleInput(SDL_Event& event){
    if(event.type==SDL_KEYDOWN || SDL_KEYUP){
        bool value= (event.type==SDL_KEYDOWN);
        switch(event.key.keysym.sym){
            case SDLK_LEFT:
                in.left=value;
                break;
            case SDLK_RIGHT:
                in.right=value;
                break;
            case SDLK_DOWN:
                in.down=value;
                break;
            case SDLK_UP:
                in.up=value;
                break;
            default:
                break;
        }
    }
}