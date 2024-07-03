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


MenuScreen :: MenuScreen(QWidget *parent) : QMainWindow(parent){

    menu = new QVBoxLayout(this);


    QPushButton* play = new QPushButton("Play!", this);
    connect(play, &QPushButton::clicked, this, &MenuScreen::startGame);


    menu->addWidget(play);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(menu);
    setCentralWidget(centralWidget);

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();

    int x = screenGeometry.center().x() - width() / 2;
    int y = screenGeometry.center().y() - height() / 2;

    this->setGeometry(x, y, WINDOW_WIDTH, WINDOW_HEIGHT);

}


void MenuScreen :: startGame(){	
	
    MainWindow *GameWindow = new MainWindow(nullptr);

    GameWindow->show();

    close();

}





