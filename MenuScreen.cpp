/* 
author Sam Feldman

date Feb 6, 2024

*/


#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <iostream>
#include "MainWindow.h"
#include "MenuScreen.h"


MenuScreen :: MenuScreen(QWidget *parent) : QMainWindow(parent){

    menu = new QVBoxLayout(this);


    QPushButton* play = new QPushButton("Play!", this);
    connect(play, &QPushButton::clicked, this, &MenuScreen::startGame);


    menu->addWidget(play);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(menu);
    setCentralWidget(centralWidget);
    this->setGeometry(300, 300, 400, 200);

}


void MenuScreen :: startGame(){	
	
    MainWindow *GameWindow = new MainWindow(nullptr);

    GameWindow->setGeometry(200, 200, 1500, 800);
	GameWindow->setFixedSize(1500, 800);

    GameWindow->show();

    close();

}





