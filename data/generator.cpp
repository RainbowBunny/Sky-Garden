#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

string flower[] = {"PUPPY", "MOON_RABBIT", "HEART_ORCHID", "GHOST_CAMPANULA", 
                   "ARIES", "DUCKLING", "LEO", "NIGHT_RABBIT", "CHICKEN_FLOWER"};

int main() {
    freopen("flower_menu.txt", "w", stdout);
    int len = 9;
    cout << len << endl;
    for (int i = 0; i < len; i++) {
        cout << flower[i % len] << endl;
        cout << 200 + i * 100 << " " << 475 << " " << 100 << " " << 100 << endl;
        
        cout << flower[i % len] << endl;
        cout << 200 + i * 100 << " " << 475 << " " << 100 << " " << 100 << endl;
        cout << 275 + i * 100 << " " << 575 << " " << 25 << " " << 25 << endl;
        cout << 255 << " " << 255 << " " << 255 << endl;

        cout << flower[i % len] << endl;
        cout << 200 + i * 100 << " " << 475 << " " << 100 << " " << 100 << endl;
        cout << 275 + i * 100 << " " << 575 << " " << 25 << " " << 25 << endl;
        cout << 255 << " " << 255 << " " << 255 << endl;
    }
}