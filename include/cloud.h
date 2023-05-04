#pragma once
#ifndef CLOUD_H
#define CLOUD_H
// Custom library
#include <constants.h>
#include <gallery.h>
#include <menu.h>

// SDL2 library
#include <SDL2/SDL.h>

// Standard library
#include <ctime>
#include <vector>

class FlowerPot {
private:
    int potFrame = 0, flowerFrame = 0;
    PictureID potImage, flowerImage;
    SDL_Rect potPosition, flowerPosition;
    Uint64 plantedTime, growthTime;
    Textbox flowerName, timeTracker;
public:
    FlowerPot();
    PictureID getPotImage() { return potImage; }
    PictureID getFlowerImage() { return flowerImage; }
    Uint64 getPlantedTime() { return plantedTime; }
    Uint64 getGrowthTime() { return growthTime; }

    void moveUp(int movingSpeed);
    void moveDown(int movingSpeed);

    void updatePotImage(PictureID newImage);
    void updateFlowerImage(PictureID newImage);
    void updatePosition(SDL_Rect newPotPosition, SDL_Rect newFlowerPosition);
    void updateFlowerName(std::string newName) { flowerName.updateText(newName); }
    void updateGrowthTime(Uint64 newGrowthTime) { growthTime = newGrowthTime; }
    void updatePlantedTime(Uint64 newTime) { plantedTime = newTime; }

    bool isChoosingPot(int mouseX, int mouseY);
    bool isChoosingFlower(int mouseX, int mouseY);

    bool placePot(PictureID newPot);
    bool placeFlower(PictureID newFlower, std::string _flowerName, Uint64 growthTime);
    bool removeFlower();
    PictureID gatherFlower();

    void renderFlowerPot(SDL_Renderer* &renderer, Gallery &gallery);
};

class CloudFloor {
private:
    int frame = 0;
    PictureID image;
    SDL_Rect cloudPosition;
    std::vector <FlowerPot> flowerPots;
public:
    CloudFloor() {}
    CloudFloor(SDL_Rect _position);
    PictureID getPotImage(int id) { return flowerPots[id].getPotImage(); }
    PictureID getFlowerImage(int id) { return flowerPots[id].getFlowerImage(); }
    Uint64 getPlantedTime(int id) { return flowerPots[id].getPlantedTime(); }
    Uint64 getGrowthTime(int id) { return flowerPots[id].getGrowthTime(); }

    void updateCloudImage(PictureID newImage) { image = newImage; }
    void updatePotImage(int id, PictureID newImage) { flowerPots[id].updatePotImage(newImage); }
    void updateFlowerImage(int id, PictureID newImage) { flowerPots[id].updateFlowerImage(newImage); }
    void updatePlantedTime(int id, Uint64 plantedTime) { flowerPots[id].updatePlantedTime(plantedTime); }
    void updatePosition(int id, SDL_Rect newPotPosition, SDL_Rect newFlowerPosition) { flowerPots[id].updatePosition(newPotPosition, newFlowerPosition); }
    void updateFlowerName(int id, std::string newName) { flowerPots[id].updateFlowerName(newName); }
    void updateGrowthTime(int id, Uint64 growthTime) { flowerPots[id].updateGrowthTime(growthTime); }

    void moveUp(int movingSpeed);
    void moveDown(int movingSpeed);

    bool isInsideFloor(int mouseX, int mouseY);
    bool placePot(int mouseX, int mouseY, PictureID potImage);
    bool placeFlower(int mouseX, int mouseY, PictureID flowerImage, std::string flowerName, Uint64 growthTime);
    bool removeFlower(int mouseX, int mouseY);
    PictureID gatherFlower(int mouseX, int mouseY);

    void renderCloudFloor(SDL_Renderer* &renderer, Gallery &gallery);
};

# endif