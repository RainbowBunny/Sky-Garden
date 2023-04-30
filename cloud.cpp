// Custom library
#include <cloud.h>

// SDL2 library

// Standard library
#include <iostream>

FlowerPot::FlowerPot() {
    potFrame = 0; flowerFrame = 0;
    potImage = NONE; flowerImage = NONE;
    potPosition = {0, 0, 0, 0}; flowerPosition = {0, 0, 0, 0};
}

void FlowerPot::moveUp() {
    potPosition.y += MOVING_SPEED;
    flowerPosition.y += MOVING_SPEED;
}

void FlowerPot::moveDown() {
    potPosition.y -= MOVING_SPEED;
    flowerPosition.y -= MOVING_SPEED;
}

void FlowerPot::updatePotImage(PictureID newImage) {
    potImage = newImage;
}

void FlowerPot::updateFlowerImage(PictureID newImage) {
    flowerImage = newImage;
}

void FlowerPot::updatePosition(SDL_Rect newPotPosition, SDL_Rect newFlowerPosition) { 
    potPosition = newPotPosition;
    flowerPosition = newFlowerPosition;
}   

void FlowerPot::renderFlowerPot(SDL_Renderer* &renderer, Gallery &gallery) {
    if (potImage != NONE) {
        if (potPosition.x >= 0 && potPosition.x + potPosition.w <= SCREEN_WIDTH && 
            potPosition.y >= 0 && potPosition.y + potPosition.h <= SCREEN_HEIGHT && 
            potPosition.w >  0 && potPosition.h >  0) {
            SDL_RenderCopy(renderer, gallery.getFrame(potImage, potFrame), nullptr, &potPosition);
        }
    }
    if (flowerImage != NONE) {
        if (flowerPosition.x >= 0 && flowerPosition.x + flowerPosition.w <= SCREEN_WIDTH && 
            flowerPosition.y >= 0 && flowerPosition.y + flowerPosition.h <= SCREEN_HEIGHT && 
            flowerPosition.w >  0 && flowerPosition.h >  0) {
            SDL_RenderCopy(renderer, gallery.getFrame(flowerImage, flowerFrame), nullptr, &flowerPosition);
        }
        
    }
}

CloudFloor::CloudFloor(SDL_Rect _position) {
    frame = 0;
    image = CLOUD;
    position = {_position.x, _position.y + _position.h * 2 / 3, _position.w, _position.h / 3};
    flowerPots.resize(9);
    int potHeight = _position.h / 3, potWidth = _position.w / 9;
    int flowerHeight = _position.h / 3, flowerWidth = _position.w / 9;

    for (int i = 0; i < 9; i++) {
        flowerPots[i].updatePosition({_position.x + i * potWidth + 10, _position.y + _position.h - potHeight - 25, potWidth - 20, potHeight - 20}, 
                                     {_position.x + i * potWidth, _position.y + _position.h - flowerHeight - potHeight - 15, flowerWidth, flowerHeight});
                                    
        flowerPots[i].updateFlowerImage(NONE);
        flowerPots[i].updatePotImage(NONE);
    }
}

void CloudFloor::moveUp() {
    position.y += MOVING_SPEED;
    for (int i = 0; i < 9; i++) {
        flowerPots[i].moveUp();
    }
}

void CloudFloor::moveDown() {
    position.y -= MOVING_SPEED;
    for (int i = 0; i < 9; i++) {
        flowerPots[i].moveDown();
    }
}

void CloudFloor::renderCloudFloor(SDL_Renderer* &renderer, Gallery &gallery) {
    if (position.x >= 0 && position.x + position.w <= SCREEN_WIDTH && 
        position.y >= 0 && position.y + position.h <= SCREEN_HEIGHT && 
        position.w >  0 && position.h >  0) {
        SDL_RenderCopy(renderer, gallery.getFrame(image, frame), nullptr, &position);
    }
    for (int i = 0; i < 9; i++) {
        flowerPots[i].renderFlowerPot(renderer, gallery);
    }
}