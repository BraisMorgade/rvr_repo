#ifndef JoinButton_h
#define JoinButton_h
#include "RenderableObject.h"

class JoinButton: public RenderableObject{
public:
    JoinButton(App* ap, int posx, int posy, int w, int h, std::string image);
    virtual ~JoinButton(){};
    virtual void handleInput(SDL_Event& event)override;
};

#endif