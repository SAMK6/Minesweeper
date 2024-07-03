/* 
author Sam Feldman

date Feb 6, 2024

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

	explicit NewGame(QWidget *parent = nullptr);
	
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

    const int WINDOW_HEIGHT = 130;
	const int WINDOW_WIDTH = 400;

};




#endif