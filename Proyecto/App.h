#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <iostream>

class App{
public:
    App();
    ~App();
    void run(std::string appName);
private:
    bool quit;
    SDL_Window* window;
    SDL_Renderer* render;
};