#pragma once
#ifndef CLOUD_H
#define CLOUD_H
// Custom library
#include <constants.h>
#include <gallery.h>

// SDL2 library
#include <SDL2/SDL.h>

// Standard library
#include <vector>

class FlowerPot {
private:
    int potFrame = 0, flowerFrame = 0;
    PictureID potImage, flowerImage;
    SDL_Rect potPosition, flowerPosition;
public:
    FlowerPot();
    PictureID getPotImage() { return potImage; }
    PictureID getFlowerImage() { return flowerImage; }
    void moveUp();
    void moveDown();
    void updatePotImage(PictureID newImage);
    void updateFlowerImage(PictureID newImage);
    void updatePosition(SDL_Rect newPotPosition, SDL_Rect newFlowerPosition);
    void renderFlowerPot(SDL_Renderer* &renderer, Gallery &gallery);
};

class CloudFloor {
private:
    int frame = 0;
    PictureID image;
    SDL_Rect position;
    std::vector <FlowerPot> flowerPots;
public:
    CloudFloor() {}
    CloudFloor(SDL_Rect _position);
    PictureID getPotImage(int id) { return flowerPots[id].getPotImage(); }
    PictureID getFlowerImage(int id) { return flowerPots[id].getFlowerImage(); }
    void updatePotImage(int id, PictureID newImage) { flowerPots[id].updatePotImage(newImage); }
    void updateFlowerImage(int id, PictureID newImage) { flowerPots[id].updateFlowerImage(newImage); }
    void updatePosition(int id, SDL_Rect newPotPosition, SDL_Rect newFlowerPosition) { flowerPots[id].updatePosition(newPotPosition, newFlowerPosition); }
    void moveUp();
    void moveDown();
    void renderCloudFloor(SDL_Renderer* &renderer, Gallery &gallery);
};

# endif