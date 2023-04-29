// Custom library
#include <mainloop.h>

// SDL2 library

// Standard library

/*
enum GameState {
    LOGGING_IN = 0,
    GAME_SCREEN,
    PAUSE_MENU,
    QUEST_MENU,
    QUITTING
};
*/

MainLoop::MainLoop(SDL_Renderer* &renderer, Gallery &gallery) {
    signInMenu = loadMenuFromFile("data/signin_menu.txt", renderer, gallery);
    signInMenu.updateBothButton("Logging in", "Logging in");
    signInMenu.updateBothButton("Sign Up", "Sign Up");

    background = Background();
    gameState = LOGGING_IN;
}

void MainLoop::renderGame(SDL_Renderer* &renderer, Gallery &gallery, int mouseX, int mouseY) {
    // std::cout << "Mainloop rendering..." << std::endl;
    background.renderBackground(renderer, gallery);
    switch (gameState) {
        case LOGGING_IN: {
            signInMenu.renderMenu(renderer, gallery, mouseX, mouseY);
            break;
        }
    }
}

void MainLoop::handleUserInput(SDL_Event e, SDL_Renderer* &renderer, Gallery &gallery) {
    switch (e.type) {
        case SDL_QUIT: {
            updateGameState(QUITTING);
            break;
        }


    }
}