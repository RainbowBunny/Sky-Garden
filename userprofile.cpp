// Custom library
#include <userprofile.h>

// SDL2 library

// Standard library

User::User() {
    
}

User::User(std::string _name, Gallery gallery) {
    name = _name;
    gallery = gallery;

    nameToFlower["PUPPY"] = PUPPY;
    nameToFlower["MOON_RABBIT"] = MOON_RABBIT;
    nameToFlower["HEART_ORCHID"] = HEART_ORCHID;
    nameToFlower["GHOST_CAMPANULA"] = GHOST_CAMPANULA;
    nameToFlower["NONE"] = NONE;

    flowerToName[PUPPY] = "PUPPY";
    flowerToName[MOON_RABBIT] = "MOON_RABBIT";
    flowerToName[HEART_ORCHID] = "HEART_ORCHID";
    flowerToName[GHOST_CAMPANULA] = "GHOST_CAMPANULA";
    flowerToName[NONE] = "NONE";

    nameToPot["POT"] = POT;
    nameToPot["NONE"] = NONE;

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
        garden[i] = CloudFloor({50, 0 - 300 * (i + 1), 900, 210});
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
        garden[i].moveDown();
    }
}

void User::moveUp() {
    for (int i = 0; i < (int)garden.size(); i++) {
        garden[i].moveUp();
    }
}

void User::renderUser(SDL_Renderer* &renderer, Gallery &gallery) {
    for (int i = 0; i <= floor; i++) {
        garden[i].renderCloudFloor(renderer, gallery);
    }
}