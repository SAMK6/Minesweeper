/* 
author Sam Feldman


*/


#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QScreen>
#include <iostream>
#include "MainWindow.h"
#include "MenuScreen.h"
#include "NewGame.h"


NewGame :: NewGame(QWidget* parent, QWidget* prevGame, int prevGameWinner, int rows, int columns, int bombs) : QMainWindow(parent){

    // set difficulty
	NUM_BOMBS = bombs;
	ROWS = rows;
	COLUMNS = columns;

    oldGame = prevGame;

    if(prevGameWinner){
        setWindowTitle("Congratulations!");
        label = new QLabel("You found all the mines and escaped!", this);
    }
    else{
        setWindowTitle("Uh-Oh!");
        label = new QLabel("You hit a bomb and exploded!", this);
    }
    label->setAlignment(Qt::AlignCenter);

    // layout stuff
    centralWidget = new QWidget(this);
    menu = new QVBoxLayout(this);


    // setup the buttons
    buttonWig = new QWidget(this);
    buttons = new QHBoxLayout(buttonWig);

    ng = new QPushButton("New Game", this);
    connect(ng, &QPushButton::clicked, this, &NewGame::newGame);
    buttons->addWidget(ng);

    mm = new QPushButton("Main Menu", this);
    connect(mm, &QPushButton::clicked, this, &NewGame::mainMenu);
    buttons->addWidget(mm);

    eg = new QPushButton("Exit", this);
    connect(eg, &QPushButton::clicked, this, &NewGame::exitGame);
    buttons->addWidget(eg);

    // put the cuttong in a horizontal layout
    buttonWig->setLayout(buttons);

    menu->addWidget(label);
    menu->addWidget(buttonWig);


    centralWidget->setLayout(menu);
    setCentralWidget(centralWidget);

    // get user screen size etc
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();

    int x = screenGeometry.center().x() - WINDOW_WIDTH / 2;
    int y = screenGeometry.center().y() - WINDOW_HEIGHT / 2;

    this->setGeometry(x, y, WINDOW_WIDTH, WINDOW_HEIGHT);

}


void NewGame :: newGame(){

    // start a new game 
    MainWindow* GameWindow = new MainWindow(nullptr, ROWS, COLUMNS, NUM_BOMBS);

    GameWindow->show();

    delete(oldGame); // to avoid memory leaks

    close();

}


void NewGame :: mainMenu(){

    // go back to the main menu
    MenuScreen* menuWindow = new MenuScreen(nullptr);

    menuWindow->show();

    delete(oldGame); // free the old game memeory

    close();

}

void NewGame :: exitGame(){
    
    delete(oldGame);

    close();

}