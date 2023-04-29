// Custom library
#include <constants.h>
#include <utils.h>
#include <gallery.h>
#include <mainloop.h>

// SDL2 library
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

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

    MainLoop gameLoop(gRenderer, gGallery);

    // Main game loop.
    while (gameLoop.getGameState() != QUITTING) {
        // Get the number of ticks at the start of the loop
        frameStart = SDL_GetTicks();

        SDL_SetRenderDrawColor(gRenderer, WHITE_COLOR.r, WHITE_COLOR.g, WHITE_COLOR.b, WHITE_COLOR.a);
        SDL_RenderClear(gRenderer);

        while (SDL_PollEvent(&e)) {
            gameLoop.handleUserInput(e, gRenderer, gGallery);
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        gameLoop.renderGame(gRenderer, gGallery, mouseX, mouseY);

        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    quitSDL(gWindow, gRenderer);
    return 0;
}