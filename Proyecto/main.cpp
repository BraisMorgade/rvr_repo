#pragma comment(lib, "libbox2d")
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "App.h"
#include "box2d/box2d.h"

extern "C" void* _input_thread(void* arg)
{
    App* server = static_cast<App*>(arg);

    server->input_thread();

    return 0;
}
extern "C" void* _client_thread(void* arg)
{
    App* server = static_cast<App*>(arg);

    server->net_thread();

    return 0;
}

int main(int argc, char** argv)
{
    App app(argv[1], argv[2], argv[3], argv[4]);

    pthread_attr_t attr;
    pthread_t id1, id2;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&id1, &attr, _client_thread, static_cast<void*>(&app));
    pthread_create(&id2, &attr, _input_thread, static_cast<void*>(&app));

    app.run("Fatal Furry");
    return 0;
}