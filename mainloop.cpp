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

    toolBoxMenu = loadMenuFromFile("data/toolbox_menu.txt", renderer, gallery);
    toolBoxMenuBackGround = loadMenuFromFile("data/background_of_toolbox_menu.txt", renderer, gallery);
    toolBoxState = "Friends";
    toolBoxMenu.updateButtonState("Friends", true);

    background = Background(gallery);
    gameState = LOGGING_IN;

    currentPlayer = User("player", gallery);
    currentPlayer.readData();
}

void MainLoop::renderGame(SDL_Renderer* &renderer, Gallery &gallery, int mouseX, int mouseY) {
    // std::cout << "Mainloop rendering..." << std::endl;
    background.renderBackground(renderer, gallery);

    switch (gameState) {

    case LOGGING_IN: {
        signInMenu.renderMenu(renderer, gallery);
        break;
    }

    case GAME_SCREEN: {
        currentPlayer.renderUser(renderer, gallery);
        toolBoxMenu.renderMenu(renderer, gallery);
        toolBoxMenuBackGround.renderMenu(renderer, gallery);
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
                std::string pressedButton = signInMenu.getPressedButton(e.button.x, e.button.y);
                
                if (pressedButton == "Sign In") {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        updateGameState(GAME_SCREEN);
                    }
                }

                break;
            }

            case GAME_SCREEN: {
                std::string pressedButton = toolBoxMenu.getPressedButton(e.button.x, e.button.y);

                if (pressedButton == "Friends") {

                    toolBoxMenu.updateButtonState(toolBoxState, false);
                    toolBoxMenu.updateButtonState("Friends", true);
                    toolBoxState = "Friends";

                } else if (pressedButton == "Pots") {

                    toolBoxMenu.updateButtonState(toolBoxState, false);
                    toolBoxMenu.updateButtonState("Pots", true);
                    toolBoxState = "Pots";

                } else if (pressedButton == "Seedlings") {

                    toolBoxMenu.updateButtonState(toolBoxState, false);
                    toolBoxMenu.updateButtonState("Seedlings", true);
                    toolBoxState = "Seedlings";

                } else {
                    std::cout << "Watermelon?" << std::endl;
                }
            }

            default: {
                break;
            } 

        }

    }

    case SDL_KEYDOWN: {

        switch(gameState) {
        case GAME_SCREEN: {
            switch (e.key.keysym.sym) {

            case SDLK_UP: {
                background.moveUp();
                currentPlayer.moveUp();
                break;
            }

            case SDLK_DOWN: {
                background.moveDown();
                currentPlayer.moveDown();
                break;
            }

            default: {
                break;
            }

            }
        }

        }

        

    }

    default: {
        break;
    }
    }
    // std::cout << "Done" << std::endl;
}