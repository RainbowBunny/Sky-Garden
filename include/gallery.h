#pragma once
#ifndef GALLERY_H
#define GALLERY_H
// Custom library

// SDL2 library
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Standard library
#include <string>
#include <vector>
#include <map>

// enumeration for different types of image.
enum PictureID {
    MENU_BACKGROUND = 0,
    BUTTON,
    PROMPT,
    BLANKSPACE,
    PUPPY,
    MOON_RABBIT,
    HEART_ORCHID,
    GHOST_CAMPANULA,
    ARIES,
    DUCKLING,
    LEO,
    NIGHT_RABBIT,
    CHICKEN_FLOWER,
    SEEDLING,
    POT,
    NORMAL_FRIEND_BUTTON,
    SPECIAL_FRIEND_BUTTON,
    NORMAL_POT_CHOOSING_BUTTON,
    SPECIAL_POT_CHOOSING_BUTTON,
    NORMAL_SEEDLING_CHOOSING_BUTTON,
    SPECIAL_SEEDLING_CHOOSING_BUTTON,
    TOOLBOX_BACKGROUND,
    HAND,
    SHOVEL,
    QUEST_LOG,
    NEW_CLOUD_FLOOR,
    NORMAL_CLOUD_FLOOR,
    TOP_CLOUD_FLOOR,
    NONE
};

class Gallery {
/*
    This is the class to load all the image in the game
*/
private:
    std::vector <std::vector <SDL_Texture*> > pictures;
    SDL_Renderer* renderer;
    TTF_Font* font;
    void loadFont(std::string path);
    std::vector <SDL_Texture*> loadTextureFromImage(std::string path, 
        int numberOfFrame, std::string extension, SDL_BlendMode blendMode);

public:
    Gallery(SDL_Renderer* _renderer);
    ~Gallery();

    void loadGamePictures();
    std::vector <SDL_Texture*> getImage(PictureID id) const { return pictures[id]; }
    SDL_Texture* getFrame(PictureID obj, int &currentFrame);
    SDL_Texture* loadTextureFromText(std::string textString, SDL_Color textColor);
    SDL_Texture* mergingTexture(SDL_Texture* texture1, SDL_Texture* texture2);
};

bool isInside(SDL_Rect rect, int pointX, int pointY);

#endif