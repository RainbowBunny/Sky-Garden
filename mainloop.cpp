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

    userManager.loadUserData("data/user_credential_data.txt");
    signInBox = loadMenuFromFile("data/sign_in_box.txt", renderer, gallery);
    signInBox.updateBothButton("__username", "Username");
    signInBox.updateBothButton("__password", "Password");
    signUpBox = loadMenuFromFile("data/sign_up_box.txt", renderer, gallery);
    signUpBox.updateBothButton("__username", "Username");
    signUpBox.updateBothButton("__password", "Password");

    notificationBox = loadMenuFromFile("data/notification_box.txt", renderer, gallery);

    toolBoxMenu = loadMenuFromFile("data/toolbox_menu.txt", renderer, gallery);
    toolBoxMenuBackGround = loadMenuFromFile("data/background_of_toolbox_menu.txt", renderer, gallery);
    toolBoxState = "Friends";
    toolBoxMenu.updateButtonState("Friends", true);
    insufficientMenu = loadMenuFromFile("data/insufficient_menu.txt", renderer, gallery);
    pauseMenu = loadMenuFromFile("data/pause_menu.txt", renderer, gallery);
    pauseMenu.updateBothButton("Log Out", "Log Out");

    background = Background(gallery);
    gameState = LOGGING_IN;

    currentObjectScreen = Button("Choosing Object", {900, 500, 100, 100},
        Textbox(NONE, {900, 500, 100, 100}, {900, 500, 100, 100}, WHITE_COLOR),
        Textbox(NONE, {900, 500, 100, 100}, {900, 500, 100, 100}, WHITE_COLOR));
    
    flowers = {{"PUPPY", PUPPY},
               {"MOON_RABBIT", MOON_RABBIT},
               {"HEART_ORCHID", HEART_ORCHID},
               {"GHOST_CAMPANULA", GHOST_CAMPANULA},
               {"ARIES", ARIES},
               {"DUCKLING", DUCKLING},
               {"LEO", LEO},
               {"NIGHT_RABBIT", NIGHT_RABBIT},
               {"CHICKEN_FLOWER", CHICKEN_FLOWER},
               {"NONE", NONE}};
    
    pots = {{"POT", POT},
            {"NONE", NONE}};

    items = {{"QUEST_LOG", QUEST_LOG},
             {"SHOVEL", SHOVEL},
             {"HAND", HAND}};
    
    utilitiesMenu = loadMenuFromFile("data/gardening_tool.txt", renderer, gallery);
}

void MainLoop::createNewProfile(std::string name) {
    std::ofstream fout("data/" + name + "_data.txt");
    fout << 1000 << std::endl;
    fout << 2 << std::endl;
    fout << "POT PUPPY 0 30\nPOT MOON_RABBIT 0 60\nPOT GHOST_CAMPANULA 0 300\nPOT ARIES 0 600\n";
    for (int i = 0; i < 14; i++) {
        fout << "NONE NONE 0 0\n";
    }
    fout << 9 << std::endl;
    fout << "PUPPY 5 30\nMOON_RABBIT 5 60\nHEART_ORCHID 5 120\nGHOST_CAMPANULA 5 300\nARIES 1 600\nDUCKLING 1 1800\nLEO 1 3600\nNIGHT_RABBIT 1 7200\nCHICKEN_FLOWER 1 18000\n";
    fout << 1 << std::endl;
    fout << "POT 1000\n";
    fout.close();
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

    case SIGN_IN_SCREEN: {
        notificationBox.renderMenu(renderer, gallery);
        signInBox.renderMenu(renderer, gallery);
        break;
    }

    case SIGN_UP_SCREEN: {
        notificationBox.renderMenu(renderer, gallery);
        signUpBox.renderMenu(renderer, gallery);
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

    case INSUFFICIENT_WARNING: {
        insufficientMenu.updateBothButton("background", "You need " + std::to_string(currentPlayer.currentRequirement()) + " flowers each types to open new floor.");
        insufficientMenu.renderMenu(renderer, gallery);
        break;
    }

    case PAUSE_MENU: {
        pauseMenu.renderMenu(renderer, gallery);
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
                    updateGameState(SIGN_IN_SCREEN);
                }
            }

            if (pressedButton == "Sign Up") {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    updateGameState(SIGN_UP_SCREEN);
                }
            }

            break;
        }

        case SIGN_IN_SCREEN: {
            std::string pressedButton;
            pressedButton = signInBox.getPressedButton(e.button.x, e.button.y);
            if (pressedButton == "username") {
                choosingBox = "username";
            } else if (pressedButton == "password") {
                choosingBox = "password";
            }
            break;
        }

        case SIGN_UP_SCREEN: {
            std::string pressedButton;
            pressedButton = signInBox.getPressedButton(e.button.x, e.button.y);
            if (pressedButton == "username") {
                choosingBox = "username";
            } else if (pressedButton == "password") {
                choosingBox = "password";
            }
            break;
        }

        case GAME_SCREEN: {

            if (currentPlayer.addingNewFloor(e.button.x, e.button.y) == 2) {
                currentPlayer.writeData();
                break;
            } else if (currentPlayer.addingNewFloor(e.button.x, e.button.y) == 1) {
                updateGameState(INSUFFICIENT_WARNING);
                break;
            }

            if (pots.count(choosingObject) && currentPlayer.addPot(e.button.x, e.button.y, pots[choosingObject])) {
                currentPlayer.writeData();
                break;
            }

            if (flowers.count(choosingObject) && currentPlayer.addFlower(e.button.x, e.button.y, flowers[choosingObject], choosingObject)) {
                currentPlayer.writeData();
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

        case INSUFFICIENT_WARNING: {
            updateGameState(GAME_SCREEN);
            break;
        }

        case PAUSE_MENU: {
            std::string pressedButton = pauseMenu.getPressedButton(e.button.x, e.button.y);
            if (pressedButton == "Log Out") {
                updateGameState(LOGGING_IN);
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
        case SIGN_IN_SCREEN: {
            if (choosingBox == "username") {
                int pressedKey = e.key.keysym.sym;
                if (pressedKey >= SDLK_a and pressedKey <= SDLK_z) {
                    currentUsername.push_back(char('a' + pressedKey - SDLK_a));
                } else if (pressedKey >= SDLK_0 and pressedKey <= SDLK_9) {
                    currentUsername.push_back(char('0' + pressedKey - SDLK_0));
                } else if (pressedKey == SDLK_BACKSPACE) {
                    if (!currentUsername.empty()) {
                        currentUsername.pop_back();
                    }
                }
            } else if (choosingBox == "password") {
                int pressedKey = e.key.keysym.sym;
                if (pressedKey >= SDLK_a and pressedKey <= SDLK_z) {
                    currentPassword.push_back(char('a' + pressedKey - SDLK_a));
                } else if (pressedKey >= SDLK_0 and pressedKey <= SDLK_9) {
                    currentPassword.push_back(char('0' + pressedKey - SDLK_0));
                } else if (pressedKey == SDLK_BACKSPACE) {
                    if (!currentPassword.empty()) {
                        currentPassword.pop_back();
                    }
                }
            }
            signInBox.updateBothButton("username", currentUsername);
            signInBox.updateBothButton("password", std::string(currentPassword.size(), '*'));
            if (e.key.keysym.sym == SDLK_RETURN) {
                if (userManager.isValidUser(currentUsername, currentPassword)) {
                    currentPlayer = User(currentUsername, renderer, gallery);
                    currentPlayer.readData();
                    updateGameState(GAME_SCREEN);
                } else {
                    updateGameState(LOGGING_IN);
                }
                currentUsername.clear();
                currentPassword.clear();
            } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                currentUsername.clear();
                currentPassword.clear();
                updateGameState(LOGGING_IN);
            }
            break;
        }

        case SIGN_UP_SCREEN: {
            if (choosingBox == "username") {
                int pressedKey = e.key.keysym.sym;
                if (pressedKey >= SDLK_a and pressedKey <= SDLK_z) {
                    currentUsername.push_back(char('a' + pressedKey - SDLK_a));
                } else if (pressedKey >= SDLK_0 and pressedKey <= SDLK_9) {
                    currentUsername.push_back(char('0' + pressedKey - SDLK_0));
                } else if (pressedKey == SDLK_BACKSPACE) {
                    if (!currentUsername.empty()) {
                        currentUsername.pop_back();
                    }
                }
            } else if (choosingBox == "password") {
                int pressedKey = e.key.keysym.sym;
                if (pressedKey >= SDLK_a and pressedKey <= SDLK_z) {
                    currentPassword.push_back(char('a' + pressedKey - SDLK_a));
                } else if (pressedKey >= SDLK_0 and pressedKey <= SDLK_9) {
                    currentPassword.push_back(char('0' + pressedKey - SDLK_0));
                } else if (pressedKey == SDLK_BACKSPACE) {
                    if (!currentPassword.empty()) {
                        currentPassword.pop_back();
                    }
                }
            }
            signUpBox.updateBothButton("username", currentUsername);
            signUpBox.updateBothButton("password", std::string(currentPassword.size(), '*'));
            if (e.key.keysym.sym == SDLK_RETURN) {
                std::cout << userManager.canCreateUser(currentUsername) << std::endl;
                if (userManager.canCreateUser(currentUsername) and currentUsername.size() >= 4 and currentPassword.size() >= 4) {
                    createNewProfile(currentUsername);
                    userManager.addUser(currentUsername, currentPassword);
                    currentPlayer = User(currentUsername, renderer, gallery);
                    currentPlayer.readData();
                    updateGameState(GAME_SCREEN);
                } else {
                    updateGameState(LOGGING_IN);
                }
                currentUsername.clear();
                currentPassword.clear();
            } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                currentUsername.clear();
                currentPassword.clear();
                updateGameState(LOGGING_IN);
            }
            break;
        }

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

            case SDLK_SPACE: {
                updateGameState(PAUSE_MENU);
                break;
            }

            default: {
                break;
            }

            }
        }

        case PAUSE_MENU: {
            switch (e.key.keysym.sym) {
            
            case SDLK_ESCAPE: {
                updateGameState(GAME_SCREEN);
                break;
            }

            default: {
                break;
            }
            }
        }

        default: {
            break;
        }

        }

        

    }

    default: {
        break;
    }
    }
    // std::cout << "Done" << std::endl;
}