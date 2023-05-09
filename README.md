
# SKY GARDEN
## Motivation
This game is an attempt to remake the web game Sky garden on Zing Me. Zing Me is a Vietnamese online social media platform which was first introduced in 2007. Zing Me used to be a very famous platform with many features, especially web game. However, due to the declining of web game player and the competition from other big media platform such as Facebook (Meta), Instagram, Twitter, etc, the platform was taken down.
Original game footage:
https://www.youtube.com/watch?v=Mv6jgnKMfgI

## Installation
Please follow these step to install the game:

- Installing mingw64 by following the instructions from this site https://www.mingw-w64.org/ .
- Clone this repo.
- Open the command prompt in this repo and run these command, make in this situation is the command to run Makefile, this command maybe differ due to the difference in the g++ 64-bit downloading process, (i.e mingw on Window may use the mingw32-make instead of make)
```
> make create
> make all 
```
- Run the main.exe file and enjoy the game.

This repo has all the required dll file and the SDL2 library so you do not need to install the library again. The game has been tested on Window and Linux but not Mac so there may be some problem when running on Mac. You can use your own config of SDL2 library.
## About the game
This game is created in C++ with the assistance of SDL2 library. Detail about this library can be found here: https://wiki.libsdl.org/SDL2/FrontPage. 
In the first screen of the game, there are two buttons: sign in and sign up, please note that the sign up button does not do anything for now. To log in, click the sign in button, there are only 5 sample players, there credential can be find in the ```data/user_credential_data.txt``` file.
After logging in, use your up and down arrow key to move between cloud floors, use your left and right arrow key to move in the list of flowers.
If you do not know the function of something on the screen, try to click it :>. The only notable thing is that please consider carefully when you use the shovel with the flower, all others function is relatively safe and may not result in any incident (hopefully).
There are some hidden function that can be trigger by the escape key on your keyboard.
In the log in screen, special characters and uppercase letter has not yet been implemented.
## Documentation
A documentation of the detail of the code can be found here:

## Future Work

The base game has been implemented but it is still very simple. Some function may be added in the future:

- Sign Up button.
- More background music in the game.
- A quest menu/trading menu to accelerate the progress of the player.
- Visiting other player garden.

The implementation of the game is a little complicated and misleading due to the lack of review and testing, so feel free to have any comment about the implementation.
