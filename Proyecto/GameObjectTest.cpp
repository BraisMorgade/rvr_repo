#include "GameObjectTest.h"
#include "SDL2/SDL_image.h"

GameObjectTest::GameObjectTest(SDL_Renderer* rd, int posx, int posy, int w, int h){
    rend=rd;
    texture=nullptr;
    posX=posx;
    posY=posy;
    width=w;
    height=h;
    SDL_Surface *surface = IMG_Load("koji.jpeg");
    if(rend!=nullptr)
        texture = SDL_CreateTextureFromSurface(rend, surface);
}
void GameObjectTest::render(){
    if(texture!=nullptr){
        SDL_Rect dstrect = { posX, posY, width, height };
        SDL_RenderCopy(rend, texture, NULL, &dstrect);
    }
}