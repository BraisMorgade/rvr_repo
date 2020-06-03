#ifndef App_h
#define App_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

private:
    bool quit;
    SDL_Window *window;
    SDL_Renderer *render;
    GameStateMachine* stateMachine;

};
#endif