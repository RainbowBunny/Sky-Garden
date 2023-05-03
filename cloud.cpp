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
    flowerName.movingUp(movingSpeed);
    timeTracker.movingUp(movingSpeed);
}

void FlowerPot::moveDown(int movingSpeed) {
    potPosition.y -= movingSpeed;
    flowerPosition.y -= movingSpeed;
    flowerName.movingDown(movingSpeed);
    timeTracker.movingDown(movingSpeed);
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
    SDL_Rect flowerNamePosition = {flowerPosition.x, flowerPosition.y - 20, flowerPosition.w, 20};
    SDL_Rect timeTrackerPosition = {potPosition.x, potPosition.y + potPosition.h, potPosition.w, 20};
    flowerName = Textbox(NONE, flowerNamePosition, flowerNamePosition, BLACK_COLOR);
    timeTracker = Textbox(NONE, timeTrackerPosition, timeTrackerPosition, BLACK_COLOR);
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

bool FlowerPot::placeFlower(PictureID newFlower, std::string _flowerName) {
    if (getFlowerImage() == NONE) {
        flowerName.updateText(_flowerName);
        updateFlowerImage(newFlower);
        updatePlantedTime(time(nullptr));
        return true;
    }
    return false;
}

std::string parseTime(Uint64 time) {
    std::string ans(8, ':');
    int tmp[3];
    tmp[0] = time / 3600; tmp[1] = (time - tmp[0] * 3600) / 60; tmp[2] = (time % 60);
    for (int i = 0; i < 3; i++) {
        ans[3 * i] = tmp[i] / 10 + '0';
        ans[3 * i + 1] = tmp[i] % 10 + '0';
    }
    return ans;
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
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (isChoosingFlower(mouseX, mouseY)) {
            flowerName.renderTextBox(renderer, gallery);
            Uint64 currentTime = time(nullptr);
            Uint64 remainingTime = 0;
            if (currentTime < plantedTime + 5) {
                remainingTime = plantedTime + 5 - currentTime;
            }
            timeTracker.updateText(parseTime(remainingTime)); 
            timeTracker.renderTextBox(renderer, gallery);
        }
        if ((Uint64)time(nullptr) - getPlantedTime() < 5) {
            SDL_RenderCopy(renderer, gallery.getFrame(SEEDLING, flowerFrame), nullptr, &flowerPosition);
            return;
        }
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
    if (time(nullptr) - getPlantedTime() < 5) {
        return NONE;
    }
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

bool CloudFloor::placeFlower(int mouseX, int mouseY, PictureID flowerImage, std::string flowerName) {
    for (int i = 0; i < 9; i++) {
        if (flowerPots[i].isChoosingFlower(mouseX, mouseY) && flowerPots[i].placeFlower(flowerImage, flowerName)) {
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