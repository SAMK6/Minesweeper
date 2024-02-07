/* 
author Sam Feldman

date Feb 6, 2024

*/


#include <QtWidgets>
#include <MyButton.h>


using namespace std;

MyButton :: MyButton(QWidget* parent) : QPushButton(parent){
	
}


void MyButton :: mousePressEvent(QMouseEvent *event){
	
	if (event->button() == Qt::LeftButton){
		emit leftClicked();
	}
	else if (event->button() == Qt::RightButton){
		emit rightClicked();
	}
	
	QPushButton::mousePressEvent(event);
	
}
