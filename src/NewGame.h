/* 
author Sam Feldman


*/

#ifndef NEW_GAME_H
#define NEW_GAME_H

#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "MainWindow.h"


class NewGame : public QMainWindow {
	
	Q_OBJECT
	
public:

	explicit NewGame(QWidget* parent = nullptr, QWidget* prevGame = nullptr, int prevGameWinner = 0, int rows = 16, int columns = 30, int bombs = 99);

private slots:
	void newGame();
    void mainMenu();
    void exitGame();


private:

    QLabel* label;
	QLayout* buttons;
    QLayout* menu;
    QWidget* buttonWig;
    QWidget* centralWidget;
    QWidget* oldGame;
    QPushButton* ng;
    QPushButton* mm;
    QPushButton* eg;


    int ROWS;
    int COLUMNS;
    int NUM_BOMBS;

    const int WINDOW_HEIGHT = 130;
	const int WINDOW_WIDTH = 400;

};


#endif