/* 
author Sam Feldman

date Feb 6, 2024

*/

#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "MainWindow.h"


class MenuScreen : public QMainWindow {
	
	Q_OBJECT
	
public:

	explicit MenuScreen(QWidget *parent = nullptr);
	
private slots:
	void startGame();

private:

	QLayout* menu;

	
	
};




#endif