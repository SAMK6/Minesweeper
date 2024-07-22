/* 
author Sam Feldman


*/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QtGui>
#include <QApplication>
#include <QMouseEvent>
#include <QIcon>
#include <iostream>
#include <random>
#include "MyButton.h"

using namespace std;

// custom window to hold the game
class MainWindow : public QMainWindow {
	
	Q_OBJECT
	
public:

	explicit MainWindow(QWidget *parent = nullptr, int = 16, int = 30, int = 99);

private slots:
	void handleRightButton();
	void handleLeftButton();
	
private:

	void clear_empty_tiles(QPushButton*);
	void show_bombs();
	
	QGridLayout* buttons;

	const int BUTTON_SIZE = 50;
	const int BUTTON_BORDER_SIZE = 2;

	int NUM_BOMBS;

	int ROWS;
	int COLUMNS;

	int gameOver = 0;
	
};



#endif