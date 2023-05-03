// Custom library
#include <userprofile.h>

// SDL2 library

// Standard library

User::User() {
    
}

User::User(std::string _name, SDL_Renderer* &renderer, Gallery &gallery) {
    currentFloor = 0;

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

    flowerChoosingMenu = loadMenuFromFile("data/flower_menu.txt", renderer, gallery);
    flowerChoosingMenu.updateActivation(0, 6);

    potChoosingMenu = loadMenuFromFile("data/pot_menu.txt", renderer, gallery);
    potChoosingMenu.updateActivation(0, 6);
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
            Uint64 plantedTime;
            fin >> pot >> flower >> plantedTime;
            garden[i].updateFlowerImage(j, nameToFlower[flower]);
            garden[i].updatePotImage(j, nameToPot[pot]);
            garden[i].updatePlantedTime(j, plantedTime);
            garden[i].updateFlowerName(j, flower);
        }
    }

    int numberOfFlowerTypes, numberOfPotTypes;
    fin >> numberOfFlowerTypes;
    for (int i = 0; i < numberOfFlowerTypes; i++) {
        std::string flowerName;
        int count;
        fin >> flowerName >> count;
        flowerData[nameToFlower[flowerName]] = count;
    }

    fin >> numberOfPotTypes;
    for (int i = 0; i < numberOfPotTypes; i++) {
        std::string potName;
        int count;
        fin >> potName >> count;
        potData[nameToPot[potName]] = count;
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
                 << flowerToName[garden[i].getFlowerImage(j)] << " " 
                 << garden[i].getPlantedTime(j) << std::endl;
        }
    }

    fout << (int)flowerData.size() << std::endl;
    for (auto flower : flowerData) {
        fout << flowerToName[flower.first] << " " << flower.second << std::endl;
    }

    fout << (int)potData.size() << std::endl;
    for (auto pot : potData) {
        fout << potToName[pot.first] << " " << pot.second << std::endl;
    }
}

void User::moveDown() {
    for (int i = 0; i < (int)garden.size(); i++) {
        if (currentFloor == 1) {
            garden[i].moveDown(420);
        } else if (currentFloor > 1) {
            garden[i].moveDown(210);
        }   
    }
    if (currentFloor > 0) {
        currentFloor--;
    }
}

void User::moveUp() {
    for (int i = 0; i < (int)garden.size(); i++) {
        if (currentFloor == 0) {
            garden[i].moveUp(420);
        } else if (currentFloor < floor){
            garden[i].moveUp(210);
        }
    }
    if (currentFloor < floor) {
        currentFloor++;
    }
}

bool User::addPot(int mouseX, int mouseY, PictureID pot) {
    if (pot == NONE or potData[pot] == 0) {
        return false;
    }
    for (int i = 0; i < floor; i++) {
        if (garden[i].isInsideFloor(mouseX, mouseY)) {
            bool ok = garden[i].placePot(mouseX, mouseY, pot);
            if (ok) {
                potData[pot]--;
            }
            return ok;
        }
    }
    return false;
}

bool User::addFlower(int mouseX, int mouseY, PictureID flower, std::string flowerName) {
    if (flower == NONE or flowerData[flower] == 0) {
        return false;
    }
    for (int i = 0; i < floor; i++) {
        if (garden[i].isInsideFloor(mouseX, mouseY)) {
            bool ok = garden[i].placeFlower(mouseX, mouseY, flower, flowerName);
            if (ok) {
                flowerData[flower]--;
            }
            return ok;
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
            PictureID flower = garden[i].gatherFlower(mouseX, mouseY);
            if (flower != NONE) {
                flowerData[flower]++;
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

void User::renderPotChoosingMenu(SDL_Renderer* &renderer, Gallery &gallery) {
    for (auto x : potData) {
        potChoosingMenu.updateBothButton(potToName[x.first], std::to_string(x.second));
    }
    potChoosingMenu.renderMenu(renderer, gallery);
}

void User::renderFlowerChoosingMenu(SDL_Renderer* &renderer, Gallery &gallery) {
    for (auto x : flowerData) {
        flowerChoosingMenu.updateBothButton(flowerToName[x.first], std::to_string(x.second));
    }
    flowerChoosingMenu.renderMenu(renderer, gallery);
}