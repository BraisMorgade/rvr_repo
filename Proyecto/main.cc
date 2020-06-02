#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

    SDL_Window *window; // Declare a pointer to an SDL_Window

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                    //    window title
        SDL_WINDOWPOS_UNDEFINED,             //    initial x position
        SDL_WINDOWPOS_UNDEFINED,             //    initial y position
        640,                                 //    width, in pixels
        480,                                 //    height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL //    flags - see below
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface *surface = IMG_Load("koji.jpeg");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    // Check that the window was successfully made
    if (window == NULL)
    {
        // In the event that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
        return 1;
    }

    bool quit = false;
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
        SDL_Rect dstrect = { 5, 5, 320, 240 };
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}