#include "MenuButton.h"
#include <iostream>
#include "App.h"
#include "GameStateMachine.h"

MenuButton::MenuButton(App* ap, int posx, int posy, 
int w, int h, std::string image):RenderableObject(ap, posx, posy, w, h, image){

}

void MenuButton::handleInput(SDL_Event& event){
    if(event.type==SDL_MOUSEBUTTONDOWN 
    && event.button.button==SDL_BUTTON_LEFT){
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if(mouseX>=posX-width/2 && mouseX<=posX+width/2 
        && mouseY>=posY-height/2 && mouseY<= posY+height/2){
            std::cout<<"posy: "<< posY<<std::endl;
            std::cout<<"mouseY: "<< mouseY<<std::endl;
            
            app->getStateMachine()->changeState("game");
        }
    }
    else if(event.type==SDL_KEYDOWN){
        if(event.key.keysym.sym==SDLK_LEFT){
            ang+=10;
        }
        else if(event.key.keysym.sym==SDLK_RIGHT){
            ang-=10;
        }
    }
}