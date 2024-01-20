# Tetris by it2000
Tetris by it2000 (provvisional name) is a simple Tetris game thought to give to the player a good, classic, and playeble Tetris experience, without things or rubbish that could disturb the player in his experience, in fact this game is designed to be simple, and to be loved from the true Tetris fans. The game has been developed following the rules of the [Tetris Guideline](https://tetris.wiki/Tetris_Guideline), a list of features that every game of Tetris should have to be considered as such.
## Graphics
From a my inspiration from the Tetris for Game Boy, this game has a monocromatic yellow graphics, without too many graphic effects which can disturb the player experience. As a response of my philosophy a game, to be liked, must be simple, minimal and dry, in fact I think that beauty is based only on its forms. This choise was also done to help color blind people like me.
## Tecnologies
This game has been developed using C++ whith the [SFML](https://www.sfml-dev.org/) multimedial library for the window and the graphics, the sprites are made with Pixelorama and the project are organized with [CMake](https://cmake.org/), a perfect tool to make multiplatform projects.
## Modifications
The project is open source under [GPL 3.0](https://www.gnu.org/licenses/gpl-3.0.en.html) licence, you can freely modify and redistribute the project without any problem, the code are organized to be understood and modified from everyone who have a medium experience with C++ and SFML. For this reason the code are on GitHub and the releases will be published here and on it.
## Build
### Windows
To build on Windows, you need to install [CMake](https://cmake.org/) and [Vcpkg](https://vcpkg.io/en/) to install SFML library. The first step is install the libraries with Vcpkg
```
vcpkg install sfml --triplet Your_Triplet
```
Make sure to specify the correct triplet for your compiler and architecture.
And then build and run...
```
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build build
cd build\Tetris_by_it2000
Tetris
```
### Linux
For Linux you can install the SFML development libraries and CMake, using the package manager of your distribution, if you don't know how to do that, please check the wiki of your distribution.
Build and run...
```
cmake -B build
cmake --build build
cd build/Tetris_by_it2000
./Tetris
```
## Where download?
The game is avaiable on [itch.io](https://itch.io/) and here: https://it2000-the-original.itch.io/tetris-by-it2000 you can download the last version of the game and leave reviews. Have fun!!
