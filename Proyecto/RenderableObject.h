#ifndef RenderableObject_h
#define RenderableObject_h
#include "GameObject.h"
#include <string>

class RenderableObject: public GameObject{
public:
    RenderableObject(App* ap, int posx, int posy, int w, int h, std::string image);
    virtual ~RenderableObject();
    virtual void render()override;
    virtual int getPositionX(){return posX;};
    virtual int getPositionY(){return posY;};
protected:
    int posX, posY;
    int height, width;
    float ang;
    SDL_RendererFlip flip;
    SDL_Texture* texture;
    SDL_Rect* clip;
};

#endif