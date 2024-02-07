/* 
author Sam Feldman

date Feb 6, 2024

*/

#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QMouseEvent>
#include <iostream>
#include <random>
#include <vector>
#include <MainWindow.h>
#include <MyButton.h>

using namespace std;

MainWindow :: MainWindow(QWidget *parent) : QMainWindow(parent){
	
	// setting up random number generator
	random_device rd;
    mt19937 gen(rd());

	// generating a list of positions will the bombs will be
	while (bombPositions.size() < 99) {
        int random_integer = uniform_int_distribution<int>(0, 480)(gen);
        bombPositions.insert(random_integer);
    }

	// Create the button grid, make "this" the parent
	buttons = new QGridLayout(this);
	
	// loop over the buttons and ad them to to the grid
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 30; j++){
			
			// make the button
			MyButton* button = new MyButton(this);
			
			// set size and location of the button
			button->setGeometry(QRect(QPoint(j * BUTTON_SIZE, i * BUTTON_SIZE), QSize(BUTTON_SIZE, BUTTON_SIZE)));
			
			// Connect button signal to appropriate slot
			connect(button, &MyButton::leftClicked, this, &MainWindow::handleLeftButton);
			connect(button, &MyButton::rightClicked, this, &MainWindow::handleRightButton);

			
			// so I can know which button was pressed later
			button->setProperty("row", i);
            button->setProperty("column", j);
			button->setProperty("isPressed", 0);
			button->setProperty("isFlagged", 0);
			
			
			// add the 
			buttons->addWidget(button, i, j);
			
		}
	}
  
  
}






// this function will recursivley reveal the tiles
void MainWindow :: clear_empty_tiles(QPushButton* button){
	
	// indicies for the button 
	int row = button->property("row").toInt();
	int column = button->property("column").toInt();
	int position = 30 * row + column;
	button->setProperty("isPressed", 1);
	
	// will fill up adjacent with the positions we could check
	vector<int> adjacentTiles = {position - 31, position - 30, position - 29, position - 1, position + 1, position + 29, position + 30, position + 31};
	int numAdjacent = 0;
	
	// this clases will remove tiles from the vector of tiles to be check when the tile we're considering is up against a wall
	if(row == 0){
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - 31), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - 30), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - 29), adjacentTiles.end());		
	}
	if(row == 15){
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + 31), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + 30), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + 29), adjacentTiles.end());		
	}
	if(column == 0){
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - 31), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - 1), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + 29), adjacentTiles.end());		
	}
	if(column == 29){
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - 29), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + 1), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + 31), adjacentTiles.end());		
	}
	
	
	// in this loop we go over all the adjacent tiles and see which ones are bombs incrementing the counter each time we find a bomb
	for (int num : adjacentTiles){
		
		auto it = bombPositions.find(num);
		if (it != bombPositions.end()){
			numAdjacent++;			
		}
		
	}
	
	
	// if the tile has no bombs around it we star clearing
	if(numAdjacent == 0){
		
		// set it to grey to mark it as 0
		button->setStyleSheet("background-color: #C0C0C0; border: none;"); // Set background color to red
	
		for (int num : adjacentTiles){
			
			int row, column;
			
			// calculate the row and column of the button based on its flattened position
			row = (num - (num % 30))/30;
			column = num % 30;
			
			// get the pointer to the button
			QLayoutItem* item = buttons->itemAtPosition(row, column);
			QPushButton* button = qobject_cast<QPushButton*>(item->widget());
			
			// if the button isn't already pressed recursivley search it 
			if(!button->property("isPressed").toBool()){
				clear_empty_tiles(button);
			}
			
		}
		
	}
	else{
		// setting the colours for the numbers basically guessed these
		if(numAdjacent == 1){
			button->setStyleSheet("color: #0000cc;");
		}
		else if(numAdjacent == 2){
			button->setStyleSheet("color: #008000;");
		}
		else if(numAdjacent == 3){
			button->setStyleSheet("color: #cc0000;");
		}
		else if(numAdjacent == 4){
			button->setStyleSheet("color: #9900bb;");
		}
		else if(numAdjacent == 5){
			button->setStyleSheet("color: #000080;");
		}
		else if(numAdjacent == 6){
			button->setStyleSheet("color: #008080;");
		}
		else if(numAdjacent == 7){
			button->setStyleSheet("color: #ff8c00;");
		}
		else if(numAdjacent == 8){
			button->setStyleSheet("color: #808080;");
		}
		
		// now set the text
		string numBombs = to_string(numAdjacent);
		button->setText(QString::fromStdString(numBombs));
		return;
	}
	
	return;
	
}

// function to handle right clicks
void MainWindow :: handleRightButton(){
	
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	
	if (button) {
		
	}
	else{
		throw("How did we get here?");
	}
	
	
	// this block toggles back and forth between flagged and not flagged
	if(!button->property("isPressed").toInt()){
		if(button->property("isFlagged").toInt()){
			
			button->setIcon(QIcon());
			button->setProperty("isFlagged", 0);
			
		}
		else{
			button->setIcon(QIcon("mine_flag.png"));
			button->setProperty("isFlagged", 1);
		}
	}
	
}

// function to handle left clicks
void MainWindow :: handleLeftButton(){
	
	// get the button/tile they pushed
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	
	// catch null pointers and setup variables
	int row, column, position;
	if (button) {
		
		// if this button has been pressed before do nothing
		if(button->property("isPressed").toInt()){
			return;
		}
				
		row = button->property("row").toInt();
		column = button->property("column").toInt();
		position = 30 * row + column;
		
	}
	else{
		throw("How did we get here?");
	}
	
	button->setIcon(QIcon());

	
	// see if the button we pressed in a bomb
	auto it = bombPositions.find(position);
	if (it != bombPositions.end()){
		
		button->setIcon(QIcon("bomb_explode.png"));
		button->setProperty("isPressed", 1);
		
		QDialog dialog;

		// Set dialog title
		dialog.setWindowTitle("Uh-Oh");
		dialog.resize(420, 100);

		// Create widgets for the dialoge it says when compiling that this line is not needed but it is 
		QLabel *label = new QLabel("You hit a bomb and exploded", &dialog);
		
		dialog.exec();
		
		close();
		
	}
	else{ // if it isn't a bomb we start clearing with the recursive helper function
		clear_empty_tiles(button);
	}

}

