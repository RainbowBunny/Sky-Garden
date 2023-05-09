// Custom library
#include <menu.h>

// SDL2 library

// Standard library
#include <unistd.h>

Uint8 castingIntToUint8(int target) { return target % (1 << 8); }

void Textbox::renderTextBox(SDL_Renderer* &renderer, Gallery &gallery) {
    if (background != NONE) {
        SDL_RenderCopy(renderer, gallery.getFrame(background, frame), nullptr, &backgroundRect);
        frame++;
    }
    
    if ((int)textString.size() > 0) {
        SDL_Rect current = {textRect.x, textRect.y, std::min(textRect.w, (int)textString.size() * 25), textRect.h};
        SDL_RenderCopy(renderer, gallery.loadTextureFromText(textString, textColor), nullptr, &current);
    }
}

Textbox createTextboxFromFile(std::ifstream &fin) {
    std::map <std::string, PictureID> stringToPictureID;

    stringToPictureID = {{"BUTTON", BUTTON},
                         {"BLANKSPACE", BLANKSPACE},
                         {"PROMPT", PROMPT},
                         {"PUPPY", PUPPY},
                         {"MOON_RABBIT", MOON_RABBIT},
                         {"HEART_ORCHID", HEART_ORCHID},
                         {"GHOST_CAMPANULA", GHOST_CAMPANULA},
                         {"ARIES", ARIES},
                         {"DUCKLING", DUCKLING},
                         {"LEO", LEO},
                         {"NIGHT_RABBIT", NIGHT_RABBIT},
                         {"CHICKEN_FLOWER", CHICKEN_FLOWER},
                         {"SEEDLING", SEEDLING},
                         {"POT", POT},
                         {"NORMAL_FRIEND_BUTTON", NORMAL_FRIEND_BUTTON},
                         {"SPECIAL_FRIEND_BUTTON", SPECIAL_FRIEND_BUTTON},
                         {"NORMAL_POT_CHOOSING_BUTTON", NORMAL_POT_CHOOSING_BUTTON},
                         {"SPECIAL_POT_CHOOSING_BUTTON", SPECIAL_POT_CHOOSING_BUTTON},
                         {"NORMAL_SEEDLING_CHOOSING_BUTTON", NORMAL_SEEDLING_CHOOSING_BUTTON},
                         {"SPECIAL_SEEDLING_CHOOSING_BUTTON", SPECIAL_SEEDLING_CHOOSING_BUTTON},
                         {"TOOLBOX_BACKGROUND", TOOLBOX_BACKGROUND},
                         {"HAND", HAND},
                         {"SHOVEL", SHOVEL},
                         {"QUEST_LOG", QUEST_LOG},
                         {"NONE", NONE}};

    /*
        Input:
        - An in file stream fin.
        Output:
        - Reading the input from the file, create a textbox.
        Format:
        string backgroundID - name of the pictures
        backgroundRect: SDL_Rect for the textbox background
        textRect: SDL_Rect for the position of the text in the textbox.
        r, g, b: int for text color 
    */
    std::string backgroundID;
    fin >> backgroundID;
    PictureID id;
    id = stringToPictureID[backgroundID];
    
    SDL_Rect _backgroundRect, _textRect;
    SDL_Color _color;
    
    fin >> _backgroundRect.x >> _backgroundRect.y >> _backgroundRect.w >> _backgroundRect.h;
    fin >> _textRect.x >> _textRect.y >> _textRect.w >> _textRect.h;

    int r, g, b;
    fin >> r >> g >> b;
    _color.r = castingIntToUint8(r);
    _color.g = castingIntToUint8(g);
    _color.b = castingIntToUint8(b);
    
    return Textbox(id, _backgroundRect, _textRect, _color);
}

void Textbox::movingLeft(int movingSpeed) {
    backgroundRect.x -= movingSpeed;
    textRect.x -= movingSpeed;
}

void Textbox::movingRight(int movingSpeed) {
    backgroundRect.x += movingSpeed;
    textRect.x += movingSpeed;
}

void Textbox::movingUp(int movingSpeed) {
    backgroundRect.y += movingSpeed;
    textRect.y += movingSpeed;
}

void Textbox::movingDown(int movingSpeed) {
    backgroundRect.y -= movingSpeed;
    textRect.y -= movingSpeed;
}

Button::Button(std::string _buttonName, SDL_Rect _buttonRect, Textbox _normal, Textbox _special) {
    buttonName = _buttonName;
    buttonRect = _buttonRect;
    normal = _normal;
    special = _special;
}

bool Button::isChoosing(int mouseX, int mouseY) {
    if (!isActive) {
        return false;
    }
    return mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
        mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h;
}

void Button::renderButton(SDL_Renderer* &renderer, Gallery& gallery) {
    if (!isActive) {
        return;
    }
    if (isSpecial) {
        special.renderTextBox(renderer, gallery);
    } else {
        normal.renderTextBox(renderer, gallery);
    }
}

void Button::movingLeft(int movingSpeed) {
    normal.movingLeft(movingSpeed);
    special.movingLeft(movingSpeed);

    buttonRect.x -= movingSpeed;
}

void Button::movingRight(int movingSpeed) {
    normal.movingRight(movingSpeed);
    special.movingRight(movingSpeed);

    buttonRect.x += movingSpeed;
}

Menu::Menu(std::vector <std::string> _buttonName, std::vector <SDL_Rect> _buttonPosition, 
    std::vector <Textbox> normal, std::vector <Textbox> special) {
    buttonList.resize((int)_buttonName.size());
    for (int i = 0; i < (int)_buttonName.size(); i++) {
        buttonList[i] = Button(_buttonName[i], _buttonPosition[i], normal[i], special[i]);
    }
}

void Menu::renderMenu(SDL_Renderer* &renderer, Gallery& gallery) {
    for (int i = 0; i < (int)buttonList.size(); i++) {
        buttonList[i].renderButton(renderer, gallery);
    }
}

void Menu::updateButtonNormal(std::string buttonName, std::string text) {
    for (int i = 0; i < (int)buttonList.size(); i++) {
        if (buttonList[i].getButtonName() == buttonName) {
            buttonList[i].updateNormal(text);
            break;
        }
    }
}

void Menu::updateButtonSpecial(std::string buttonName, std::string text) {
    for (int i = 0; i < (int)buttonList.size(); i++) {
        if (buttonList[i].getButtonName() == buttonName) {
            buttonList[i].updateSpecial(text);
            break;
        }
    }
}

void Menu::updateBothButton(std::string buttonName, std::string text) {
    for (int i = 0; i < (int)buttonList.size(); i++) {
        if (buttonList[i].getButtonName() == buttonName) {
            buttonList[i].updateNormal(text);
            buttonList[i].updateSpecial(text);
            break;
        }
    }
}

std::string Menu::getNormalButtonText(std::string buttonName) {
    for (int i = 0; i < (int)buttonList.size(); i++) {
        if (buttonList[i].getButtonName() == buttonName) {
            return buttonList[i].getTextNormal();
        }
    }
    return "NONE";
}

Menu loadMenuFromFile(std::string file, SDL_Renderer* &renderer, Gallery &gallery) {
    /*
        Data format:
        name 
        x y w h 
        textbox1
        textbox2
        string name: name of the button
        x y w h - SDL_Rect, position of the menu button
        (format of textbox in createTextboxFromFile)
    */
    std::ifstream fin(file);
    if (!fin.is_open()) {
        logError(std::cout, "Can not open file: " + file, true);
    }
    int n;
    fin >> n;

    std::vector <std::string> buttonName(n);
    std::vector <SDL_Rect> buttonPosition(n);
    std::vector <Textbox> normal(n), special(n);

    for (int i = 0; i < n; i++) {
        getline(fin, buttonName[i]); // taking the '\n' character
        getline(fin, buttonName[i]);
        fin >> buttonPosition[i].x >> buttonPosition[i].y >> buttonPosition[i].w >> buttonPosition[i].h;
        normal[i] = createTextboxFromFile(fin), special[i] = createTextboxFromFile(fin);
    }
    return Menu(buttonName, buttonPosition, normal, special);
}

std::string Menu::getPressedButton(int mouseX, int mouseY) {
    for (int i = 0; i < (int)buttonList.size(); i++) {
        if (buttonList[i].getActivationState() == true && buttonList[i].isChoosing(mouseX, mouseY)) {
            return buttonList[i].getButtonName();
        }
    }
    return "NONE";
}

void Menu::updateButtonState(std::string buttonName, bool newState) {
    for (int i = 0; i < (int)buttonList.size(); i++) {
        if (buttonList[i].getButtonName() == buttonName) {
            buttonList[i].updateState(newState);
        }
    }
}

void Menu::movingLeft() {
    if (startingPoint + windowLength < (int)buttonList.size()) {
        startingPoint++;
    } else {
        return;
    }

    buttonList[startingPoint - 1].updateActivationState(false);
    buttonList[startingPoint + windowLength - 1].updateActivationState(true);
    for (int i = 0; i < (int)buttonList.size(); i++) {
        buttonList[i].movingLeft(100);
    }

}

void Menu::movingRight() {
    if (startingPoint > 0) {
        startingPoint--;
    } else {
        return;
    }
    buttonList[startingPoint + windowLength].updateActivationState(false);
    buttonList[startingPoint].updateActivationState(true);
    for (int i = 0; i < (int)buttonList.size(); i++) {
        buttonList[i].movingRight(100);
    }
}

void Menu::updateActivation(int newStartingPoint, int newWindowLength) {
    startingPoint = newStartingPoint;
    windowLength = newWindowLength;
    for (int i = 0; i < (int)buttonList.size(); i++) {
        buttonList[i].updateActivationState(false);
        if (i >= newStartingPoint && i < newStartingPoint + newWindowLength) {
            buttonList[i].updateActivationState(true);
        }
    }
}

Background::Background(Gallery &gallery) {
    /*
    enum GameState {
        LOGGING_IN = 0,
        GAME_SCREEN,
        PAUSE_MENU,
        QUEST_MENU
    };
    */

    gallery = gallery;
    currentState = LOGGING_IN;
    srcRect = {0, 0, 0, 0};
    int tmp = 0;
    SDL_QueryTexture(gallery.getFrame(MENU_BACKGROUND, tmp), nullptr, nullptr, &srcRect.w, &srcRect.h);
    dstRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    backgroundID.push_back(MENU_BACKGROUND);
    backgroundID.push_back(MENU_BACKGROUND);
    backgroundID.push_back(MENU_BACKGROUND);
    backgroundID.push_back(MENU_BACKGROUND);
}

void Background::renderBackground(SDL_Renderer* &renderer, Gallery &gallery) {
    if (backgroundID[currentState] == NONE) {
        return;
    }

    if (dstRect.x >= 0 && dstRect.x + dstRect.w <= SCREEN_WIDTH && 
        dstRect.y >= 0 && dstRect.y + dstRect.h <= SCREEN_HEIGHT && 
        dstRect.w >  0 && dstRect.h >  0) {
        SDL_RenderCopy(renderer, gallery.getFrame(backgroundID[currentState], frame), &srcRect, &dstRect);
        frame++;
    }
    
}

void Background::setBackgroundState(GameState state) {
    currentState = state;
    frame = 0;

    srcRect = {0, 0, 0, 0};
    int tmp = 0;
    SDL_QueryTexture(gallery->getFrame(backgroundID[state], tmp), nullptr, nullptr, &srcRect.w, &srcRect.h);
    dstRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}