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

void FlowerPot::moveUp(int movingSpeed) {
    potPosition.y += movingSpeed;
    flowerPosition.y += movingSpeed;
}

void FlowerPot::moveDown(int movingSpeed) {
    potPosition.y -= movingSpeed;
    flowerPosition.y -= movingSpeed;
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

bool FlowerPot::isChoosingPot(int mouseX, int mouseY) {
    return isInside(potPosition, mouseX, mouseY) | isInside(flowerPosition, mouseX, mouseY);
}

bool FlowerPot::isChoosingFlower(int mouseX, int mouseY) {
    return isInside(potPosition, mouseX, mouseY) | isInside(flowerPosition, mouseX, mouseY);
}

bool FlowerPot::placePot(PictureID newPot) {
    if (getPotImage() == NONE) {
        updatePotImage(newPot);
        return true;
    }
    return false;
}

bool FlowerPot::placeFlower(PictureID newFlower) {
    if (getFlowerImage() == NONE) {
        updateFlowerImage(newFlower);
        return true;
    }
    return false;
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

bool FlowerPot::removeFlower() {
    if (getFlowerImage() != NONE) {
        updateFlowerImage(NONE);
        return true;
    }
    return false;
}

PictureID FlowerPot::gatherFlower() {
    PictureID currentFlower = getFlowerImage();
    removeFlower();
    return currentFlower;
}

CloudFloor::CloudFloor(SDL_Rect _position) {
    frame = 0;
    image = NONE;
    cloudPosition = _position;

    flowerPots.resize(9);
    int potHeight = 60, potWidth = 60;
    int flowerHeight = 60, flowerWidth = 60;

    for (int i = 0; i < 9; i++) {
        flowerPots[i].updatePosition({_position.x + i * (potWidth + 16) + 190 - 1, _position.y + _position.h - potHeight - 40, potWidth - 2, potHeight}, 
                                     {_position.x + i * (potWidth + 16) + 190 - 1, _position.y + _position.h - flowerHeight - potHeight - 30, flowerWidth - 2, flowerHeight});
                                    
        flowerPots[i].updateFlowerImage(NONE);
        flowerPots[i].updatePotImage(NONE);
    }
}

void CloudFloor::moveUp(int movingSpeed) {
    cloudPosition.y += movingSpeed;
    for (int i = 0; i < 9; i++) {
        flowerPots[i].moveUp(movingSpeed);
    }
}

void CloudFloor::moveDown(int movingSpeed) {
    cloudPosition.y -= movingSpeed;
    for (int i = 0; i < 9; i++) {
        flowerPots[i].moveDown(movingSpeed);
    }
}

bool CloudFloor::isInsideFloor(int mouseX, int mouseY) {
    return isInside(cloudPosition, mouseX, mouseY);
}

bool CloudFloor::placePot(int mouseX, int mouseY, PictureID potImage) {
    for (int i = 0; i < 9; i++) {
        if (flowerPots[i].isChoosingPot(mouseX, mouseY) && flowerPots[i].placePot(potImage)) {
            return true;
        }
    }
    return false;
}

bool CloudFloor::placeFlower(int mouseX, int mouseY, PictureID flowerImage) {
    for (int i = 0; i < 9; i++) {
        if (flowerPots[i].isChoosingFlower(mouseX, mouseY) && flowerPots[i].placeFlower(flowerImage)) {
            return true;
        }
    }
    return false;
}

bool CloudFloor::removeFlower(int mouseX, int mouseY) {
    for (int i = 0; i < 9; i++) {
        if (flowerPots[i].isChoosingFlower(mouseX, mouseY)) {
            return flowerPots[i].removeFlower();
        }
    }
    return false;
}

PictureID CloudFloor::gatherFlower(int mouseX, int mouseY) {
    for (int i = 0; i < 9; i++) {
        if (flowerPots[i].isChoosingFlower(mouseX, mouseY)) {
            return flowerPots[i].gatherFlower();
        }
    }
    return NONE;
}

void CloudFloor::renderCloudFloor(SDL_Renderer* &renderer, Gallery &gallery) {
    if (cloudPosition.w >  0 && cloudPosition.h >  0) {
        SDL_RenderCopy(renderer, gallery.getFrame(image, frame), nullptr, &cloudPosition);
    }
    for (int i = 0; i < 9; i++) {
        flowerPots[i].renderFlowerPot(renderer, gallery);
    }
}