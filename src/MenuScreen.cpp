/* 
author Sam Feldman


*/


#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QScreen>
#include <QComboBox>
#include <iostream>
#include "MainWindow.h"
#include "MenuScreen.h"


MenuScreen :: MenuScreen(QWidget *parent) : QMainWindow(parent){

    setWindowTitle("Minsweeper");

    // create they layout
    menu = new QVBoxLayout(this);

    // setup the button
    play = new QPushButton("Play!", this);
    connect(play, &QPushButton::clicked, this, &MenuScreen::startGame);
    menu->addWidget(play);

    // setup the difficulty combobox
    difficulty = new QComboBox(this);
    difficulty->addItem("Select Difficulty");
    difficulty->addItem("Beginner");
    difficulty->addItem("Intermediate");
    difficulty->addItem("Expert");

    connect(difficulty, QOverload<const QString &>::of(&QComboBox::currentTextChanged), this, &MenuScreen::difficulty_select);

    menu->addWidget(difficulty);

    // setup layout and central widget
    centralWidget = new QWidget(this);
    centralWidget->setLayout(menu);
    setCentralWidget(centralWidget);

    // get the users screen geometry
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();
    int x = screenGeometry.center().x() - WINDOW_WIDTH / 2;
    int y = screenGeometry.center().y() - WINDOW_HEIGHT / 2;

    this->setGeometry(x, y, WINDOW_WIDTH, WINDOW_HEIGHT);

}


void MenuScreen :: startGame(){
    
    MainWindow *GameWindow;

    // create the new game according to difficulty
    if(DIFFICULTY == 'b'){
        GameWindow = new MainWindow(nullptr, 9, 9, 10);
    }
    else if(DIFFICULTY == 'i'){
        GameWindow = new MainWindow(nullptr, 16, 16, 40);
    }
    else if(DIFFICULTY == 'e'){
        GameWindow = new MainWindow(nullptr, 16, 30, 99);
    }
    else{
        return;
    }

    GameWindow->show();

    close();

}

void MenuScreen :: difficulty_select(const QString diff){

    // simple combobox handler to set difficulty
    if(diff == "Beginner"){
        DIFFICULTY = 'b';
    }
    else if(diff == "Intermediate"){
        DIFFICULTY = 'i';
    }
    else if(diff == "Expert"){
        DIFFICULTY = 'e';
    }


}






