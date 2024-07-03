/* 
author Sam Feldman

date Feb 6, 2024

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



NewGame :: NewGame(QWidget* parent) : QMainWindow(parent){


    setWindowTitle("Uh-Oh!");    
    
    centralWidget = new QWidget(this);

    menu = new QVBoxLayout(this);

    label = new QLabel("You hit a bomb and exploded!");
    label->setAlignment(Qt::AlignCenter);

    // setup the buttons
    buttonWig = new QWidget(this);
    buttons = new QHBoxLayout(buttonWig);

    QPushButton* ng = new QPushButton("New Game", this);
    connect(ng, &QPushButton::clicked, this, &NewGame::newGame);
    buttons->addWidget(ng);

    QPushButton* mm = new QPushButton("Main Menu", this);
    connect(mm, &QPushButton::clicked, this, &NewGame::mainMenu);
    buttons->addWidget(mm);

    QPushButton* eg = new QPushButton("Exit", this);
    connect(eg, &QPushButton::clicked, this, &NewGame::exitGame);
    buttons->addWidget(eg);

    buttonWig = new QWidget(this);
    buttonWig->setLayout(buttons);

    menu->addWidget(label);
    menu->addWidget(buttonWig);


    centralWidget->setLayout(menu);
    setCentralWidget(centralWidget);

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();

    int x = screenGeometry.center().x() - WINDOW_WIDTH / 2;
    int y = screenGeometry.center().y() - WINDOW_HEIGHT / 2;

    this->setGeometry(x, y, WINDOW_WIDTH, WINDOW_HEIGHT);

}


void NewGame :: newGame(){


    MainWindow* GameWindow = new MainWindow(nullptr);

    GameWindow->show();

    close();


}


void NewGame :: mainMenu(){

    MenuScreen* menuWindow = new MenuScreen(nullptr);

    menuWindow->show();

    close();

}

void NewGame :: exitGame(){

    close();

}