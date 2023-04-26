// Custom library
#include <constants.h>
#include <utils.h>
#include <gallery.h>
#include <mainloop.h>

// SDL2 library
#include <SDL2/SDL.h>

// Standard library
#include <iostream>
#include <utility>

const char* gameTitle = "Game";

// Remember, do not forget argc, argv
int main(int argc, char **argv) {
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;

    initSDL(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, gameTitle);

    // Creating game object
    Gallery gGallery(gRenderer);
    
    // Event handler
    SDL_Event e;

    // Time frame to maintain a constant FPS
    Uint32 frameStart;
    int frameTime;

    // Main game loop.
    while (true) {
        // Get the number of ticks at the start of the loop
        frameStart = SDL_GetTicks();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    quitSDL(gWindow, gRenderer);
    return 0;
}