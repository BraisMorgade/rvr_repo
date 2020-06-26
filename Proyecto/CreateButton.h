#ifndef CreateButton_h
#define CreateButton_h
#include "RenderableObject.h"

class CreateButton: public RenderableObject{
public:
    CreateButton(App* ap, int posx, int posy, int w, int h, std::string image);
    virtual ~CreateButton(){};
    virtual void handleInput(SDL_Event& event)override;
};

#endif