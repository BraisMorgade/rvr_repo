#ifndef App_h
#define App_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "box2d/box2d.h"
#include "Socket.h"
#include <string.h>
#include <iostream>

class GameStateMachine;

class App
{
public:
    App(const char* s, const char* p, const char* n, const char* pl);
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
    GameStateMachine* getStateMachine(){
        return stateMachine;
    }
    Socket* getSocket(){
        return &socket;
    }

    int getPlayer(){
        return player;
    }

    virtual void input_thread();

    virtual void net_thread();

private:
    bool quit;
    SDL_Window *window;
    SDL_Renderer *render;
    b2Vec2 gravity;
    b2World* world;
    GameStateMachine* stateMachine;
    Socket socket;
    Socket* remote;
    std::string nick;
    int player;

    Serializable* localInput;
    Serializable* remoteInput; 
};
#endif