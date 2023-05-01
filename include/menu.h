#pragma once
// Custom library
#include <constants.h>
#include <utils.h>
#include <gallery.h>

// SDL2 library
#include <SDL2/SDL.h>

// Standard library
#include <fstream>
#include <vector>
#include <string>
#include <map>

class Textbox {
private:
    int frame = 0;
    PictureID background;
    SDL_Rect backgroundRect, textRect;
    SDL_Color textColor;
    std::string textString;
public:
    Textbox() {}
    Textbox(PictureID _background, SDL_Rect _backgroundRect, SDL_Rect _textRect, SDL_Color _textColor) { 
        background = _background; backgroundRect = _backgroundRect; textRect = _textRect; textColor = _textColor; }
    void updateText(std::string newText) { textString = newText; }
    void renderTextBox(SDL_Renderer* &renderer, Gallery &gallery);
};

class Button {
private:
    int frame = 0;
    PictureID frameName;
    std::string buttonName;
    SDL_Rect buttonRect;
    Textbox normal, special;
    bool isSpecial = false;
public:
    Button() {};
    Button(std::string buttonName, SDL_Rect buttonRect, Textbox _normal, Textbox _special);
    std::string getButtonName() { return buttonName; }
    bool isChoosing(int mouseX, int mouseY);
    void updateBoth(std::string text) { updateNormal(text); updateSpecial(text); }
    void updateNormal(std::string text) { normal.updateText(text); }
    void updateSpecial(std::string text) { special.updateText(text); }
    void updateState(bool newState) { isSpecial = newState; }
    void renderButton(SDL_Renderer* &renderer, Gallery& gallery);
};

class Menu {
private:
    std::vector <Button> buttonList;
public:
    Menu() {}
    Menu(std::vector <std::string> _buttonName, std::vector <SDL_Rect> _buttonPosition, 
        std::vector <Textbox> normal, std::vector <Textbox> special);
    void renderMenu(SDL_Renderer* &renderer, Gallery& gallery);
    void updateButtonNormal(std::string buttonName, std::string text);
    void updateButtonSpecial(std::string buttonName, std::string text);
    void updateBothButton(std::string buttonName, std::string text);
    void updateButtonState(std::string buttonName, bool newState);
    std::string getPressedButton(int mouseX, int mouseY);
};

Menu loadMenuFromFile(std::string file, SDL_Renderer* &renderer, Gallery &gallery);

class Background {
private:
    int frame = 0;
    GameState currentState;
    SDL_Rect srcRect, dstRect;
    std::vector <PictureID> backgroundID;
    Gallery *gallery;
public:
    Background() {}
    Background(Gallery &gallery);
    void setBackgroundState(GameState state);
    void moveDown();
    void moveUp();
    void renderBackground(SDL_Renderer* &renderer, Gallery &gallery);
};

Textbox createTextboxFromFile(std::ifstream &fin);