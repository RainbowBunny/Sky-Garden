# Sky-Garden

To add a flower to the game, we need to modify:
- The nameToFlower and flowerToName map in function User::User class user in userprofile.cpp. (Create a PictureID with the name and map)
- stringToPictureID in function createTextboxFromFile in menu.cpp. (Create a PictureID with the name and map)
- map flowers in function MainLoop::MainLoop in mainloop.cpp. (Create a PictureID with the name and map)
- User data in folder data (file with _data in name). (Add the name of the flower)
- flower_menu.txt (using the generator.cpp file).
To add a pot to the game, we need to modify:
- The nameToPot and potToName map in function User::User in class user in userprofile.cpp. (Create a PictureID with the name and map)
- stringToPictureID in function createTextboxFromFile in menu.cpp. (Create a PictureID with the name and map)
- map pots in function MainLoop::MainLoop in mainloop.cpp. (Create a PictureID with the name and map)
- User data in folder data (file with _data in name). (Add the name of the pot)
- pot_menu.txt (using the generator.cpp file).
To add an item to the game, we need to modify:
- map items in function MainLoop::MainLoop in mainloop.cpp.
- Modify the data/gardening_tool.txt.