#ifndef GameObject_h
#define GameObject_h
#include <SDL2/SDL.h>

class App;

class GameObject{
public:
    GameObject(App* ap){app=ap;};
    ~GameObject(){};
    virtual void start(){}
    virtual void update(){};
    virtual void render(){};
    virtual void handleInput(SDL_Event& event){};
protected:
    App* app;
};
#endif