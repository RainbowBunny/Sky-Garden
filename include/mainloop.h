#pragma once
// Custom library
#include <constants.h>
#include <utils.h>
#include <gallery.h>
#include <menu.h>
#include <cloud.h>

// SDL2 library

// Standard library

class MainLoop {
private:
    Menu signInMenu;
    Background background;
    
    CloudFloor potato;

    GameState gameState;
public:
    MainLoop(SDL_Renderer* &renderer, Gallery &gallery);
    void updateGameState(GameState state) { gameState = state; }
    void renderGame(SDL_Renderer* &renderer, Gallery &gallery, int mouseX, int mouseY);
    void handleUserInput(SDL_Event e, SDL_Renderer* &renderer, Gallery &gallery);
    GameState getGameState() { return gameState; }
};