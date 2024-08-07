# Modern Minesweeper

## Installation instructions

Installing my Minesweeper is simple and can be done with a few simple commands. Since this is a QT application you will need QT version 6 or greater and a C++ compiler (if you are on macOS or any debian based linux version you already have the C++ compiler). 

### Installing QT

To Install QT on macOS:

```
sudo brew install qt6
```

and on linux:

```
sudo apt install qt6-base-dev
```


### Installing the Game

First clone the repository, this can be done in the terminal with:

```
git clone https://github.com/SAMK6/Minesweeper.git
```

next navigate to /Minesweeper/src:

```
cd Minesweeper/src
```

then run the qmake utility to generate the makefile (the project file is already configured):

```
qmake6
```

finally build the application:

```
make
```

If all steps were successful there will be an application called Minesweeper in Minesweeper/src ready to go, enjoy!
