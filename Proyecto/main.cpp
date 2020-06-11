#pragma comment(lib, "libbox2d")
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "App.h"
#include "box2d/box2d.h"

int main(int argc, char *argv[])
{
    App app;
    app.run("Fatal Furry");
   
    return 0;
}