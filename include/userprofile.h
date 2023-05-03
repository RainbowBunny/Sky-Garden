#pragma once

// Custom library
#include <cloud.h>
#include <utils.h>
#include <menu.h>

// SDL2 library

// Standard library
#include <fstream>
#include <vector>

class User {
private:
    int coin, floor, currentFloor;
    std::vector <CloudFloor> garden;
    std::string name;
    
    std::map <std::string, PictureID> nameToFlower;
    std::map <PictureID, std::string> flowerToName;

    std::map <std::string, PictureID> nameToPot;
    std::map <PictureID, std::string> potToName;

    std::map <PictureID, int> flowerData, potData;
public:
    Menu flowerChoosingMenu, potChoosingMenu;
    
    User();
    User(std::string _name, SDL_Renderer* &renderer, Gallery &gallery);
    
    int getFloor() { return floor; }
    int getCurrentFloor() { return currentFloor; }

    void createProfile();
    void readData();
    void writeData();

    void moveDown();
    void moveUp();

    bool addPot(int x, int y, PictureID pot);
    bool addFlower(int x, int y, PictureID flower, std::string flowerName);
    bool removeFlower(int mouseX, int mouseY);
    bool gatherFlower(int mouseX, int mouseY);

    void renderUser(SDL_Renderer* &renderer, Gallery &gallery);
    void renderPotChoosingMenu(SDL_Renderer* &renderer, Gallery &gallery);
    void renderFlowerChoosingMenu(SDL_Renderer* &renderer, Gallery &gallery);
};