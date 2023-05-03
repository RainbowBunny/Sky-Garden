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

    currentPlayer = User("player", renderer, gallery);
    currentPlayer.readData();

    currentObjectScreen = Button("Choosing Object", {900, 500, 100, 100},
        Textbox(NONE, {900, 500, 100, 100}, {900, 500, 100, 100}, WHITE_COLOR),
        Textbox(NONE, {900, 500, 100, 100}, {900, 500, 100, 100}, WHITE_COLOR));
    
    flowers = {{"PUPPY", PUPPY},
               {"MOON_RABBIT", MOON_RABBIT},
               {"HEART_ORCHID", HEART_ORCHID},
               {"GHOST_CAMPANULA", GHOST_CAMPANULA},
               {"NONE", NONE}};
    
    pots = {{"POT", POT},
            {"NONE", NONE}};

    items = {{"QUEST_LOG", QUEST_LOG},
             {"SHOVEL", SHOVEL},
             {"HAND", HAND}};
    
    utilitiesMenu = loadMenuFromFile("data/gardening_tool.txt", renderer, gallery);
}

void MainLoop::renderGame(SDL_Renderer* &renderer, Gallery &gallery, int mouseX, int mouseY) {
    // std::cout << "Mainloop rendering..." << std::endl;
    if (gameState == GAME_SCREEN && currentPlayer.getCurrentFloor() > 0) {
        
    } else {
        background.renderBackground(renderer, gallery);
    }

    switch (gameState) {

    case LOGGING_IN: {
        signInMenu.renderMenu(renderer, gallery);
        break;
    }

    case GAME_SCREEN: {
        currentPlayer.renderUser(renderer, gallery);
        toolBoxMenu.renderMenu(renderer, gallery);
        toolBoxMenuBackGround.renderMenu(renderer, gallery);
        
        if (toolBoxState == "Friends") {
            
        } else if (toolBoxState == "Pots") {
            currentPlayer.renderPotChoosingMenu(renderer, gallery);
        } else if (toolBoxState == "Seedlings") {
            currentPlayer.renderFlowerChoosingMenu(renderer, gallery);
        }
        
        currentObjectScreen.renderButton(renderer, gallery);

        utilitiesMenu.renderMenu(renderer, gallery);
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

                if (pots.count(choosingObject) && currentPlayer.addPot(e.button.x, e.button.y, pots[choosingObject])) {
                    break;
                }

                if (flowers.count(choosingObject) && currentPlayer.addFlower(e.button.x, e.button.y, flowers[choosingObject], choosingObject)) {
                    break;
                }

                if (choosingObject == "SHOVEL" && currentPlayer.removeFlower(e.button.x, e.button.y)) {
                    break;
                }

                if (choosingObject == "HAND" && currentPlayer.gatherFlower(e.button.x, e.button.y)) {
                    break;
                }

                std::string pressedButton;

                pressedButton = toolBoxMenu.getPressedButton(e.button.x, e.button.y);

                if (pressedButton == "Friends") {

                    toolBoxMenu.updateButtonState(toolBoxState, false);
                    toolBoxMenu.updateButtonState("Friends", true);
                    toolBoxState = "Friends";
                    break;

                } else if (pressedButton == "Pots") {

                    toolBoxMenu.updateButtonState(toolBoxState, false);
                    toolBoxMenu.updateButtonState("Pots", true);
                    toolBoxState = "Pots";
                    break;

                } else if (pressedButton == "Seedlings") {

                    toolBoxMenu.updateButtonState(toolBoxState, false);
                    toolBoxMenu.updateButtonState("Seedlings", true);
                    toolBoxState = "Seedlings";
                    break;

                }

                pressedButton = utilitiesMenu.getPressedButton(e.button.x, e.button.y);
                if (pressedButton == "QUEST_LOG") {
                    break;
                } else if (pressedButton == "HAND" or pressedButton == "SHOVEL") {
                    choosingObject = pressedButton;
                    currentObjectScreen.updateBothImage(items[pressedButton]);
                    break;
                }

                if (toolBoxState == "Friends") {

                } else if (toolBoxState == "Pots") {
                    pressedButton = currentPlayer.potChoosingMenu.getPressedButton(e.button.x, e.button.y);
                    choosingObject = pressedButton;
                    currentObjectScreen.updateBothImage(pots[pressedButton]);
                    break;
                } else if (toolBoxState == "Seedlings") {
                    pressedButton = currentPlayer.flowerChoosingMenu.getPressedButton(e.button.x, e.button.y);
                    choosingObject = pressedButton;
                    currentObjectScreen.updateBothImage(flowers[pressedButton]);
                    break;
                }
                
                break;
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
                currentPlayer.moveUp();
                break;
            }

            case SDLK_DOWN: {
                currentPlayer.moveDown();
                break;
            }

            case SDLK_LEFT: {
                currentPlayer.flowerChoosingMenu.movingRight();
                break;
            }

            case SDLK_RIGHT: {
                currentPlayer.flowerChoosingMenu.movingLeft();
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