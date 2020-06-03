#ifndef GameObject_h
#define GameObject_h
#include <SDL2/SDL.h>
class GameObject{
public:
    GameObject(){};
    ~GameObject(){};
    virtual void start()=0;
    virtual void update()=0;
    virtual void render()=0;
    virtual void handleInput(SDL_Event& event)=0;
};
#endif