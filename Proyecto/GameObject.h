#ifndef GameObject_h
#define GameObject_h
#include <SDL2/SDL.h>

class App;

class GameObject{
public:
    GameObject(App* ap){app=ap; readyDestr=false;};
    virtual ~GameObject(){};
    virtual void start(){}
    virtual void update(){};
    virtual void render(){};
    virtual bool isReadyToDestroy(){return readyDestr;};
    virtual void readyToDestroy(bool ready){
        readyDestr=ready;
    };
    virtual void handleInput(SDL_Event& event){};
protected:
    App* app;
    bool readyDestr;
};
#endif