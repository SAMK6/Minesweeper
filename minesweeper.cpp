/* 
author Sam Feldman

date Feb 6, 2024

*/

#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <MainWindow.h>

// this file will act as the main file 


using namespace std;

int main(int argc, char* argv[]){
	
	QApplication app(argc, argv);
	MainWindow GameWindow;
    GameWindow.setGeometry(200, 200, 1500, 800);
	GameWindow.setFixedSize(1500, 800);
	GameWindow.show();
	
	
	
	return app.exec();
	
}

