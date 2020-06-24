#ifndef GameState_h
#define GameState_h
#include <list>
#include "GameObject.h"

class App;

class GameState{
public:
    GameState(App* ap);
    ~GameState(){};
    virtual void start();
    virtual void update();
    virtual void render(SDL_Renderer* render);
    virtual void handleInput(SDL_Event& event);
    virtual void end();
    virtual void send(){};
    virtual void receive(){};
    virtual void destroyReadyEntities();
protected:
    std::list<GameObject*> objects;
    App* app;
};
#endif
