// Custom library
#include <gallery.h>
#include <utils.h>

// SDL2 library

// Standard library
#include <string>
#include <algorithm>

Gallery::Gallery(SDL_Renderer* _renderer) {
    renderer = _renderer;
    loadGamePictures();
}

Gallery::~Gallery() {
    /*
        Destructor for the gallery, swapping with the empty vector to free memory
    */
    std::vector <std::vector <SDL_Texture*> > tmp;
    std::swap(pictures, tmp);
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
    std::vector <SDL_Texture*> animation(numberOfFrame);
    for (int i = 0; i < numberOfFrame; i++) {
        SDL_Surface* loadedSurface = IMG_Load((path + "_" + std::to_string(i) + extension).c_str());
        if (loadedSurface == nullptr) {
            logSDLError(std::cout, "Can not load image: " + path, true);            
        }
        animation[i] = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_SetTextureBlendMode(animation[i], blendMode);
    }

    return animation;
}

/*
    enum PictureID {

    };
*/

void Gallery::loadGamePictures() {
    /*
        This class will load image into the gallery.
        Remember to update accroading to the PICTURE_ID.
        Format: Use loadTextureFromImage
    */
}