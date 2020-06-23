#include "App.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "GameContactListener.h"

App::App(const char* s, const char* p, const char* n, const char* pl):socket(s,p), nick(n)
{
    localInput=nullptr;
    remoteInput=nullptr;
    quit = false;
    render = nullptr;
    window = nullptr;
    gravity= b2Vec2(0.0f, 10.0f);
    std::string str(pl);
    if(str=="1"){
        player=1;
    }
    else {
        player=2;
    }
}

App::~App()
{
}

void App::input_thread(){
    while(true){
        if(localInput!=nullptr)
            socket.send(*localInput, socket);
    }
}

void App::net_thread(){
    while(true){
        socket.recv(*remoteInput);
    }
}

void App::run(std::string appName)
{
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        appName.c_str(),                     //    window title
        SDL_WINDOWPOS_UNDEFINED,             //    initial x position
        SDL_WINDOWPOS_UNDEFINED,             //    initial y position
        640,                                 //    width, in pixels
        480,                                 //    height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL //    flags - see below
    );

    render = SDL_CreateRenderer(window, -1, 0);

    SDL_Event event;

    world=new b2World(gravity);
    stateMachine=new GameStateMachine(this);

    world->SetContactListener(new GameContactListener());
    stateMachine->getCurrentState()->start();
    float stepTime=1.0f/60.0f;
    GameState* currState= stateMachine->getCurrentState();
    while (!quit)
    {
        Uint32 time=SDL_GetTicks();
        currState->update();
        currState->render(render);
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                currState->handleInput(event);
                break;
            }
        }
        currState->destroyReadyEntities();
        world->Step(stepTime, 6, 2);
        stepTime = (float)(SDL_GetTicks()-time)/1000.0f;
        currState=stateMachine->getCurrentState();
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}