#ifndef MenuButton_h
#define MenuButton_h
#include "RenderableObject.h"

class MenuButton: public RenderableObject{
public:
    MenuButton(App* ap, int posx, int posy, int w, int h, std::string image);
    ~MenuButton();
    virtual void handleInput(SDL_Event& event)override;
private:

};

#endif