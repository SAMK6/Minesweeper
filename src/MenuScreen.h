/* 
author Sam Feldman


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
	void difficulty_select(const QString);

private:

	QLayout* menu;
	QPushButton* play;
	QComboBox *difficulty;
	QWidget *centralWidget;

	const int WINDOW_HEIGHT = 200;
	const int WINDOW_WIDTH = 400;

	char DIFFICULTY = 's';
	
};




#endif