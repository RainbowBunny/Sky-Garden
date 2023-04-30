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
    signInMenu.updateBothButton("Sign In", "Sign In");
    signInMenu.updateBothButton("Sign Up", "Sign Up");

    background = Background(gallery);
    gameState = LOGGING_IN;

    potato = CloudFloor({100, 0, 900, 300});
}

void MainLoop::renderGame(SDL_Renderer* &renderer, Gallery &gallery, int mouseX, int mouseY) {
    // std::cout << "Mainloop rendering..." << std::endl;
    background.renderBackground(renderer, gallery);
    potato.render(renderer, gallery);
    switch (gameState) {

        case LOGGING_IN: {
            signInMenu.renderMenu(renderer, gallery, mouseX, mouseY);
            break;
        }

        default: {
            break;
        }
    }
    // std::cout << "Done" << std::endl;
}

void MainLoop::handleUserInput(SDL_Event e, SDL_Renderer* &renderer, Gallery &gallery) {
    // std::cout << "Begin handling user input" << std::endl;
    switch (e.type) {
        case SDL_QUIT: {
            updateGameState(QUITTING);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {

            switch (gameState) {

                case LOGGING_IN: {
                    std::string pressedButton = signInMenu.getPressedButton(e.button.x, e.motion.y);
                    
                    if (pressedButton == "Sign In") {
                        if (e.button.button == SDL_BUTTON_LEFT) {
                            updateGameState(GAME_SCREEN);
                        }
                    }

                    break;
                }

                default: {

                } 

            }

        }

        case SDL_KEYDOWN: {

            switch (e.key.keysym.sym) {

                case SDLK_UP: {
                    background.moveUp();
                    break;
                }

                case SDLK_DOWN: {
                    background.moveDown();
                    break;
                }

                default: {
                    
                }

            }

        }

        default: {
            break;
        }
    }
    // std::cout << "Done" << std::endl;
}