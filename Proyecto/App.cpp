#include "App.h"
#include "GameStateMachine.h"
#include "GameState.h"
App* App::instance=0;

App::App()
{
    quit = false;
    render = nullptr;
    window = nullptr;
}

App* App::getInstance(){
    if (instance == nullptr)
    {
        instance = new App();
    }
    return instance;
}

App::~App()
{
}
void App::run(std::string appName)
{
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

    SDL_Window *window; // Declare a pointer to an SDL_Window

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        appName.c_str(),                     //    window title
        SDL_WINDOWPOS_UNDEFINED,             //    initial x position
        SDL_WINDOWPOS_UNDEFINED,             //    initial y position
        640,                                 //    width, in pixels
        480,                                 //    height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL //    flags - see below
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event event;

    GameStateMachine::getInstance()->getCurrentState()->start();

    while (!quit)
    {
        GameStateMachine::getInstance()->getCurrentState()
        ->update();
        GameStateMachine::getInstance()->getCurrentState()
        ->render(render);
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                GameStateMachine::getInstance()->getCurrentState()
                ->handleInput(event);
                break;
            }
        }

    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    /*
    SDL_Surface *surface = IMG_Load("koji.jpeg");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    // Check that the window was successfully made
    if (window == NULL)
    {
        // In the event that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
        quit=true;
    }

    SDL_Event event;

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    */
}