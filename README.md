
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
Now you can create a new user, note that the username and password need to have length >= 4.
To log in, click the sign in button, please do not stole other people data in ```data/user_credential_data.txt``` file.
After logging in, use your up and down arrow key to move between cloud floors, use your left and right arrow key to move in the list of flowers.
If you do not know the function of something on the screen, try to click it :>. The only notable thing is that please consider carefully when you use the shovel with the flower, all others function is relatively safe and may not result in any incident (hopefully).
There are some hidden function that can be trigger by the escape key on your keyboard.
In the log in screen, special characters and uppercase letter has not yet been implemented.
## How to play
- Create an account with the ```sign up button``` or ```log in``` if you already have an account, note that the user name and passwords' length must be ```greater than or equal 4```.
- To escape from the boxes, try to use ```esc key```.
- To move between cloudfloor, use ```up arrow``` and ```down arrow```.
- Gathering using the ```gatherer button```.
- To remove a flower use the ```shovel```, please note that the removed flower ```will not be returned```.
- There are a ```pot menu``` and a ```flower menu``` to help you plant flower.
- Use ```left and right arrow``` to navigate in the flower menu and pot menu.
## Documentation
A documentation of the detail of the code can be found here:

## Game Screenshots

Start menu screenshot: 
![Alt text](https://github.com/RainbowBunny/Sky-Garden/blob/main/StartMenu.png)

In game screenshot: 
![Alt text](https://github.com/RainbowBunny/Sky-Garden/blob/main/InGame.png)

## Future Work

The base game has been implemented but it is still very simple. Some function may be added in the future:

- More background music in the game.
- A quest menu/trading menu to accelerate the progress of the player.
- Visiting other player garden.

The implementation of the game is a little complicated and misleading due to the lack of review and testing, so feel free to have any comment about the implementation.
