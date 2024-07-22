/* 
author Sam Feldman


*/

#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include "MainWindow.h"
#include "MenuScreen.h"

// this file will act as the main file 


using namespace std;


int main(int argc, char* argv[]){


	QApplication app(argc, argv);
	MenuScreen menu;

	menu.show();
	
	return app.exec();
	
}