#include "Fighter.h"
#include <math.h>

Fighter::Fighter(App* ap, int posx, int posy, int w, int h, std::string image, BodyType type)
:PhysicsObject(ap, posx, posy, w, h, image, type){
    in.left=false;
    in.right=false;
    in.up=false;
    in.down=false;
    jumpState=FALLING;
}

void Fighter::update(){
    PhysicsObject::update();
    switch(jumpState){
        case GROUNDED:
            if(in.up){
                if(in.right)
                    body->SetLinearVelocity(b2Vec2(1, -5));
                else if(in.left)
                    body->SetLinearVelocity(b2Vec2(-1, -5));
                else
                    body->SetLinearVelocity(b2Vec2(0, -5));

                jumpState=RISING;
            }
            else if(in.right)
                body->SetLinearVelocity(b2Vec2(1,body->GetLinearVelocity().y));
            else if(in.left)
                body->SetLinearVelocity(b2Vec2(-1,body->GetLinearVelocity().y));
            else
                body->SetLinearVelocity(b2Vec2(0,body->GetLinearVelocity().y));
            break;
        case FALLING:
            if(abs(body->GetLinearVelocity().y)<=0.05)
                jumpState=GROUNDED;
            break;
        case RISING:
            if(abs(body->GetLinearVelocity().y)<=0.05)
                jumpState=APEX;
            break;
        case APEX:
            if(abs(body->GetLinearVelocity().y)>0.05)
                jumpState=FALLING;
            break;
        default:
            break;
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
    //enviar Input al otro cliente
}

Fighter::~Fighter(){
}