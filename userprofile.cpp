// Custom library
#include <userprofile.h>

// SDL2 library

// Standard library

User::User() {
    
}

User::User(std::string _name, Gallery gallery) {
    name = _name;
    gallery = gallery;

    nameToFlower = {{"PUPPY", PUPPY},
                    {"MOON_RABBIT", MOON_RABBIT},
                    {"HEART_ORCHID", HEART_ORCHID},
                    {"GHOST_CAMPANULA", GHOST_CAMPANULA},
                    {"NONE", NONE}};

    flowerToName = {{PUPPY, "PUPPY"},
                    {MOON_RABBIT, "MOON_RABBIT"},
                    {HEART_ORCHID, "HEART_ORCHID"},
                    {GHOST_CAMPANULA, "GHOST_CAMPANULA"},
                    {NONE, "NONE"}};

    nameToPot = {{"POT", POT},
                 {"NONE", NONE}};

    potToName = {{POT, "POT"},
                 {NONE, "NONE"}};

    potToName[POT] = "POT";
    potToName[NONE] = "NONE";
}

void User::createProfile() {
    coin = 2000;
    floor = 1;
    garden.emplace_back();
    for (int i = 0; i < 9; i++) {

    }
}

void User::readData() {
    std::cout << "Reading user data" << std::endl;
    std::ifstream fin("data/" + name + "_data.txt");

    if (!fin.is_open()) {
        logError(std::cout, "Can not file user profile: " + name + "\n", true);
    }

    fin >> coin;
    fin >> floor;
    garden.resize(floor + 1);

    for (int i = 0; i <= floor; i++) {
        garden[i] = CloudFloor({50, 0 - 210 * (i + 1), 900, 210});
        if (i == floor) {
            garden[i].updateCloudImage(NEW_CLOUD_FLOOR);
            continue;
        }
        if (i == floor - 1) {
            garden[i].updateCloudImage(TOP_CLOUD_FLOOR);
        } else {
            garden[i].updateCloudImage(NORMAL_CLOUD_FLOOR);
        }

        for (int j = 0; j < 9; j++) {
            std::string pot, flower;
            fin >> pot >> flower;
            garden[i].updateFlowerImage(j, nameToFlower[flower]);
            garden[i].updatePotImage(j, nameToPot[pot]);
        }
    }

    std::cout << "Finished reading user data" << std::endl;
    fin.close();
}

void User::writeData() {
    std::ofstream fout("data/" + name + "_data.txt");

    fout << coin << std::endl;
    fout << floor << std::endl;

    for (int i = 0; i < floor; i++) {
        for (int j = 0; j < 9; j++) {
            fout << potToName[garden[i].getPotImage(j)] << " " 
                 << flowerToName[garden[i].getFlowerImage(j)] << std::endl;
        }
    }
}

void User::moveDown() {
    for (int i = 0; i < (int)garden.size(); i++) {
        garden[i].moveDown(210);
    }
}

void User::moveUp() {
    for (int i = 0; i < (int)garden.size(); i++) {
        garden[i].moveUp(210);
    }
}

bool User::addPot(int mouseX, int mouseY, PictureID pot) {
    for (int i = 0; i < floor; i++) {
        if (garden[i].isInsideFloor(mouseX, mouseY)) {
            return garden[i].placePot(mouseX, mouseY, pot);
        }
    }
    return false;
}

bool User::addFlower(int mouseX, int mouseY, PictureID flower) {
    for (int i = 0; i < floor; i++) {
        if (garden[i].isInsideFloor(mouseX, mouseY)) {
            return garden[i].placeFlower(mouseX, mouseY, flower);
        }
    }
    return false;
}

bool User::removeFlower(int mouseX, int mouseY) {
    for (int i = 0; i < floor; i++) {
        if (garden[i].isInsideFloor(mouseX, mouseY)) {
            return garden[i].removeFlower(mouseX, mouseY);
        }
    }
    return false;
}

bool User::gatherFlower(int mouseX, int mouseY) {
    for (int i = 0; i < floor; i++) {
        if (garden[i].isInsideFloor(mouseX, mouseY)) {
            if (garden[i].gatherFlower(mouseX, mouseY) != NONE) {
                return true;
            }
            return false;
        }
    }
    return false;
}

void User::renderUser(SDL_Renderer* &renderer, Gallery &gallery) {
    for (int i = 0; i < (int)garden.size(); i++) {
        garden[i].renderCloudFloor(renderer, gallery);
    }
}