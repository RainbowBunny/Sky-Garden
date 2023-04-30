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
    FlowerPot(PictureID _image, SDL_Rect _position);
    void updatePosition(SDL_Rect newPostion);
    void moveUp();
    void moveDown();
    void updatePotImage(PictureID newImage);
    void updateFlowerImage(PictureID newImage);
    void updatePosition(SDL_Rect newPotPosition, SDL_Rect newFlowerPosition);
    void render(SDL_Renderer* &renderer, Gallery &gallery);
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
    void moveUp();
    void moveDown();
    void render(SDL_Renderer* &renderer, Gallery &gallery);
};

# endif