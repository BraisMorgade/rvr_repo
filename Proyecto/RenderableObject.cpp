#include "RenderableObject.h"
#include <SDL2/SDL_image.h>
#include "App.h"

RenderableObject::RenderableObject(App* ap, int posx, int posy, int w, int h, std::string image): GameObject(ap){
    
    posX=posx;
    posY=posy;
    width=w;
    height=h;
    texture = nullptr;
    SDL_Surface *surface = IMG_Load(image.c_str());
    if (app->getRender() != nullptr)
        texture = SDL_CreateTextureFromSurface(app->getRender(), surface);
    
}

void RenderableObject::render(){
    
    if (texture != nullptr)
    {
        SDL_Rect dstrect = {posX-width/2, posY-height/2, width, height};
        SDL_RenderCopy(app->getRender(), texture, NULL, &dstrect);
    }
}