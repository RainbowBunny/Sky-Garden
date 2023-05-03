#pragma once
// Custom library
#include <constants.h>
#include <utils.h>
#include <gallery.h>
#include <menu.h>
#include <cloud.h>
#include <userprofile.h>

// SDL2 library

// Standard library
#include <map>

class MainLoop {
private:
    Menu signInMenu;
    Menu toolBoxMenu, toolBoxMenuBackGround;

    Menu utilitiesMenu;
    Background background;
    
    User currentPlayer;

    std::string toolBoxState;
    std::string choosingObject;
    Button currentObjectScreen;

    GameState gameState;

    std::map <std::string, PictureID> pots, flowers, items;    
public:
    MainLoop(SDL_Renderer* &renderer, Gallery &gallery);
    void updateGameState(GameState state) { gameState = state; }
    void renderGame(SDL_Renderer* &renderer, Gallery &gallery, int mouseX, int mouseY);
    void handleUserInput(SDL_Event e, SDL_Renderer* &renderer, Gallery &gallery);
    GameState getGameState() { return gameState; }
};