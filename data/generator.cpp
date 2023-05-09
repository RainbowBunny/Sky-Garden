#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

string flower[] = {"PUPPY", "MOON_RABBIT", "HEART_ORCHID", "GHOST_CAMPANULA", 
                   "ARIES", "DUCKLING", "LEO", "NIGHT_RABBIT", "CHICKEN_FLOWER"};

int main() {
    // freopen("flower_menu.txt", "w", stdout);
    // int len = 9;
    // cout << len << endl;
    // for (int i = 0; i < len; i++) {
    //     cout << flower[i % len] << endl;
    //     cout << 200 + i * 100 << " " << 475 << " " << 100 << " " << 100 << endl;
        
    //     cout << flower[i % len] << endl;
    //     cout << 200 + i * 100 << " " << 475 << " " << 100 << " " << 100 << endl;
    //     cout << 275 + i * 100 << " " << 575 << " " << 25 << " " << 25 << endl;
    //     cout << 255 << " " << 255 << " " << 255 << endl;

    //     cout << flower[i % len] << endl;
    //     cout << 200 + i * 100 << " " << 475 << " " << 100 << " " << 100 << endl;
    //     cout << 275 + i * 100 << " " << 575 << " " << 25 << " " << 25 << endl;
    //     cout << 255 << " " << 255 << " " << 255 << endl;
    // }
    for (int i = 0; i < 4; i++) {
        std::string filename = "player" + std::to_string(i) + "_data.txt";
        ofstream fout(filename);
        fout << "1000\n2\n";
        for (int j = 0; j < 18; j++) {
            if (j == 0) {
                fout << "POT PUPPY 0 30\n";
            } else if (j == 1) {
                fout << "POT MOON_RABBIT 0 60\n";
            } else if (j == 2) {
                fout << "POT GHOST_CAMPANULA 0 300\n";
            } else if (j == 3) {
                fout << "POT ARIES 0 600\n";
            } else {
                fout << "NONE NONE 0 0\n";
            }
        }
        fout << "9\nPUPPY 5 30\nMOON_RABBIT 5 60\nHEART_ORCHID 5 120\nGHOST_CAMPANULA 5 300\nARIES 1 600\nDUCKLING 1 1800\nLEO 1 3600\nNIGHT_RABBIT 1 7200\nCHICKEN_FLOWER 1 18000\n1\nPOT 1000";
    }
}