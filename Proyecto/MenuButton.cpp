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
        if(mouseX>=posX && mouseX<=posX+width 
        && mouseY>=posY && mouseY<= posY+height){
            std::cout<<"Cambio de estado"<<std::endl;
            app->getStateMachine()->changeState("game");
        }
    }
}