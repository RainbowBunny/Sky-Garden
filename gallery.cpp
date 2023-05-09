// Custom library
#include <gallery.h>
#include <utils.h>

// SDL2 library

// Standard library
#include <string>
#include <algorithm>

Gallery::Gallery(SDL_Renderer* _renderer) {
    renderer = _renderer;
    loadFont("font/Southern.ttf");
    loadGamePictures();
}

Gallery::~Gallery() {

}

void Gallery::loadFont(std::string path) {
    font = TTF_OpenFont(path.c_str(), 18);
    if (font == nullptr) {
        logSDLError(std::cout, "Can not open font: " + path, true);
    }
}

std::vector <SDL_Texture*> Gallery::loadTextureFromImage(std::string path, 
    int numberOfFrame, std::string extension, SDL_BlendMode blendMode) {
    /*
        This function is used to load an animation series
        Input:
            Path (string): The path to the animation list
            numberOfFrame (int): Number of frame of the animation
        Output:
            animation (vector <SDL_Texture*>): The loaded animation of the object.
    */
    std::vector <SDL_Surface*> surfaceList(numberOfFrame); 
    std::vector <SDL_Texture*> animation(numberOfFrame);
    std::cout << path << std::endl;
    for (int i = 0; i < numberOfFrame; i++) {
        surfaceList[i] = IMG_Load((path + "_" + std::to_string(i) + extension).c_str());
        if (path == "circ")
            SDL_SetColorKey(surfaceList[i], SDL_TRUE, SDL_MapRGB(surfaceList[i]->format, 0x00, 0xFF, 0xFF));
        else
            SDL_SetColorKey(surfaceList[i], SDL_TRUE, SDL_MapRGB(surfaceList[i]->format, 0xFF, 0xFF, 0xFF));
        if (surfaceList[i] == nullptr) {
            logSDLError(std::cout, "Can not load image: " + path, true);            
        }
        animation[i] = SDL_CreateTextureFromSurface(renderer, surfaceList[i]);
        SDL_SetTextureBlendMode(animation[i], blendMode);
    }

    return animation;
}

void Gallery::loadGamePictures() {
    /*
    enum PictureID {
        MENU_BACKGROUND = 0,
        BUTTON,
        NONE
    };
    */

    // loading background

    pictures.push_back(loadTextureFromImage("image/menu_background", 1, ".jpg", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/button", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/prompt", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/blankspace", 1, ".png", SDL_BLENDMODE_BLEND));
    
    // loading flowers
    pictures.push_back(loadTextureFromImage("image/flower/puppy", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/flower/moon_rabbit", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/flower/heart_orchid", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/flower/ghost_campanula", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/flower/aries", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/flower/duckling", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/flower/leo", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/flower/night_rabbit", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/flower/chicken_flower", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/flower/seedling", 1, ".png", SDL_BLENDMODE_BLEND));

    
    // loading pots
    pictures.push_back(loadTextureFromImage("image/pot/pot", 1, ".png", SDL_BLENDMODE_BLEND));

    // loading game icons
    pictures.push_back(loadTextureFromImage("image/game_icon/normal_friend_icon", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/game_icon/choosing_friend_icon", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/game_icon/normal_pot_icon", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/game_icon/choosing_pot_icon", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/game_icon/normal_seedling_icon", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/game_icon/choosing_seedling_icon", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/game_icon/toolbox_background", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/game_icon/gatherer", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/game_icon/shovel", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/game_icon/quest_log", 1, ".png", SDL_BLENDMODE_BLEND));

    // loading cloud
    pictures.push_back(loadTextureFromImage("image/cloud/new_cloud_floor", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/cloud/normal_cloud_floor", 1, ".png", SDL_BLENDMODE_BLEND));
    pictures.push_back(loadTextureFromImage("image/cloud/top_cloud_floor", 1, ".png", SDL_BLENDMODE_BLEND));
}

SDL_Texture* Gallery::getFrame(PictureID obj, int &currentFrame) {
    if (currentFrame < 0) {
        logError(std::cout, "Invalid frame ", true);
    }
    currentFrame %= pictures[obj].size();
    return pictures[obj][currentFrame];
}

SDL_Texture* Gallery::loadTextureFromText(std::string textString, SDL_Color textColor) {
    SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, textString.c_str(), textColor);
    if (loadedSurface == nullptr) {
        logSDLError(std::cout, "Can not create surface from text: " + textString, true);
    }
    SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_free(loadedSurface);
    return loadedTexture;
}

SDL_Texture* Gallery::mergingTexture(SDL_Texture* texture1, SDL_Texture* texture2) {
    /*
        Return the combination of two texture:
        Set render target to a texture and draw both texture on renderer.
    */
    SDL_Texture* target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1000, 1000);
    SDL_SetRenderTarget(renderer, target);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);
    SDL_RenderFillRect(renderer, nullptr);
    
    // SDL_RenderCopy(renderer, texture1, nullptr, nullptr);
    // SDL_RenderCopy(renderer, texture2, nullptr, nullptr);

    SDL_SetRenderTarget(renderer, nullptr);
    return target;
}

bool isInside(SDL_Rect rect, int pointX, int pointY) {
    return rect.x <= pointX && rect.x + rect.w >= pointX &&
           rect.y <= pointY && rect.y + rect.h >= pointY;
}