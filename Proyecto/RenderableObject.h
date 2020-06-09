#ifndef RenderableObject_h
#define RenderableObject_h
#include "GameObject.h"
#include <string>

class RenderableObject: public GameObject{
public:
    RenderableObject(App* ap, int posx, int posy, int w, int h, std::string image);
    virtual ~RenderableObject(){};
    virtual void render()override;
protected:
    int posX, posY;
    int height, width;
    SDL_Texture* texture;
};

#endif