#pragma once
#ifndef MAINLOOP_H
#define MAINLOOP_H
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
    Menu signInBox, signUpBox, notificationBox;
    UserManager userManager;

    Menu toolBoxMenu, toolBoxMenuBackGround, insufficientMenu;
    Menu utilitiesMenu, pauseMenu;
    Background background;
    User currentPlayer;

    std::string toolBoxState, choosingObject, choosingBox, currentUsername, currentPassword;
    Button currentObjectScreen;

    GameState gameState;

    std::map <std::string, PictureID> pots, flowers, items;    
public:
    MainLoop(SDL_Renderer* &renderer, Gallery &gallery);
    void updateGameState(GameState state) { gameState = state; }
    void renderGame(SDL_Renderer* &renderer, Gallery &gallery, int mouseX, int mouseY);
    void handleUserInput(SDL_Event e, SDL_Renderer* &renderer, Gallery &gallery);
    void createNewProfile(std::string name);
    GameState getGameState() { return gameState; }
};

#endif