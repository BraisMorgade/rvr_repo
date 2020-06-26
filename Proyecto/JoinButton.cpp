#include "JoinButton.h"
#include "App.h"
#include "GameStateMachine.h"
#include "MainMenu.h"

JoinButton::JoinButton(App* ap, int posx, int posy, int w, int h, std::string image):RenderableObject(ap, posx, posy, w, h, image){
    
}

void JoinButton::handleInput(SDL_Event& event){
    if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT){
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if(mouseX>=posX-width/2 && mouseX<=posX+width/2 
        && mouseY>=posY-height/2 && mouseY<= posY+height/2){
            MainMenu* menu=static_cast<MainMenu*>(app->getStateMachine()->getCurrentState());
            menu->joining=true;
            menu->creating=false;
        }
    }
}
