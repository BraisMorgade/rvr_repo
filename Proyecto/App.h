#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <iostream>

class App
{
public:

    static App *getInstance();
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
    App();
    ~App();
    App(App &) = delete;
    App &operator=(const App &) = delete;
    bool quit;
    SDL_Window *window;
    SDL_Renderer *render;
    static App *instance;
};