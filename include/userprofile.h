#pragma once

// Custom library
#include <cloud.h>
#include <utils.h>

// SDL2 library

// Standard library
#include <fstream>
#include <vector>

class User {
private:
    int coin, floor;
    std::vector <CloudFloor> garden;
    std::string name;
    
    std::map <std::string, PictureID> nameToFlower;
    std::map <PictureID, std::string> flowerToName;

    std::map <std::string, PictureID> nameToPot;
    std::map <PictureID, std::string> potToName;
public:
    User();
    User(std::string _name, Gallery gallery);
    void createProfile();
    void readData();
    void writeData();

    void moveDown();
    void moveUp();

    bool addPot(int x, int y, PictureID pot);
    bool addFlower(int x, int y, PictureID flower);
    bool removeFlower(int mouseX, int mouseY);
    bool gatherFlower(int mouseX, int mouseY);

    void renderUser(SDL_Renderer* &renderer, Gallery &gallery);
};