#ifndef App_h
#define App_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "box2d/box2d.h"
#include <string.h>
#include <iostream>

class GameStateMachine;

class App
{
public:
    App();
    ~App();
    void run(std::string appName);
    SDL_Window *getWindow()
    {
        return window;
    }
    SDL_Renderer *getRender()
    {
        return render;
    }
    b2World* getWorld(){
        return world;
    }
private:
    bool quit;
    SDL_Window *window;
    SDL_Renderer *render;
    b2Vec2 gravity;
    b2World* world;
    GameStateMachine* stateMachine;

};
#endif