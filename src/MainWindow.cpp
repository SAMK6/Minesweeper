/* 
author Sam Feldman

date Feb 6, 2024

*/

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QtGui>
#include <QApplication>
#include <QMouseEvent>
#include <QIcon>
#include <iostream>
#include <random>
#include <set>
#include "MyButton.h"
#include "MainWindow.h"
#include "NewGame.h"

using namespace std;

MainWindow :: MainWindow(QWidget *parent, int rows, int columns, int bombs) : QMainWindow(parent){
	
	// set difficulty
	NUM_BOMBS = bombs;
	ROWS = rows;
	COLUMNS = columns;

	setWindowTitle("Minesweeper");


	// setting up random number generator
	random_device rd;
    mt19937 gen(rd());
	set<int> bombPositions;

	// generating a list of positions will the bombs will be

	while ((int)bombPositions.size() < NUM_BOMBS) {
        int random_integer = uniform_int_distribution<int>(0, ROWS * COLUMNS)(gen);
        bombPositions.insert(random_integer);
    }


	// Create the button grid, make "this" the parent
	buttons = new QGridLayout(this);
	
	// loop over the buttons and ad them to to the grid
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLUMNS; j++){
			
			// make the button
			MyButton* button = new MyButton(this);
			
			// set size and location of the button
			button->setGeometry(QRect(QPoint(j * BUTTON_SIZE, i * BUTTON_SIZE), QSize(BUTTON_SIZE, BUTTON_SIZE)));
			button->setStyleSheet(QString("QPushButton {    background-color: #bababa;    border: %1px solid #333333;   }").arg(BUTTON_BORDER_SIZE));
			
			// Connect button signal to appropriate slot
			connect(button, &MyButton::leftClicked, this, &MainWindow::handleLeftButton);
			connect(button, &MyButton::rightClicked, this, &MainWindow::handleRightButton);

			
			// so I can know which button was pressed later
			button->setProperty("row", i);
            button->setProperty("column", j);
			button->setProperty("isPressed", 0);
			button->setProperty("isFlagged", 0);


			auto it = bombPositions.find((i * COLUMNS) + j);

			if (it != bombPositions.end()){
				button->setProperty("isBomb", 1);			
			}
			else{
				button->setProperty("isBomb", 0);			
			}
			
			
			// add the button to the layout
			buttons->addWidget(button, i, j);
			
		}


	}

	QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();

    int x = screenGeometry.center().x() - BUTTON_SIZE*COLUMNS / 2;
    int y = screenGeometry.center().y() - BUTTON_SIZE*ROWS / 2;

	this->setGeometry(x, y, BUTTON_SIZE*COLUMNS, BUTTON_SIZE*ROWS);
  	this->setFixedSize(BUTTON_SIZE*COLUMNS, BUTTON_SIZE*ROWS);
  
}






// this function will recursivley reveal the tiles
void MainWindow :: clear_empty_tiles(QPushButton* button){

	
	// indicies for the button 
	int bRow = button->property("row").toInt(), bColumn = button->property("column").toInt();
	int position = COLUMNS * bRow + bColumn;
	if(!button->property("isFlagged").toInt()){
		button->setProperty("isPressed", 1);
	}
	
	// will fill up adjacent with the positions we could check
	vector<int> adjacentTiles = {position - COLUMNS + 1, position - COLUMNS, position - COLUMNS - 1, position - 1, position + 1, position + COLUMNS - 1, position + COLUMNS, position + COLUMNS + 1};
	int numAdjacent = 0;
	
	// this clauses will remove tiles from the vector of tiles to be check when the tile we're considering is up against a wall
	if(bRow == 0){
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - COLUMNS + 1), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - COLUMNS), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - COLUMNS - 1), adjacentTiles.end());		
	}
	if(bRow == ROWS - 1){
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + COLUMNS + 1), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + COLUMNS), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + COLUMNS - 1), adjacentTiles.end());		
	}
	if(bColumn == 0){
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - COLUMNS - 1), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - 1), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + COLUMNS - 1), adjacentTiles.end());		
	}
	if(bColumn == COLUMNS - 1){
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position - COLUMNS + 1), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + 1), adjacentTiles.end());		
		adjacentTiles.erase(remove(adjacentTiles.begin(), adjacentTiles.end(), position + COLUMNS + 1), adjacentTiles.end());		
	}
	
	
	// in this loop we go over all the adjacent tiles and see which ones are bombs incrementing the counter each time we find a bomb
	for (int num : adjacentTiles){

		int row, column;

		column = num % COLUMNS;
		row = (num - column)/COLUMNS;
		
		if (qobject_cast<QPushButton*>(buttons->itemAtPosition(row, column)->widget())->property("isBomb").toInt()){
			numAdjacent++;			
		}
		
	}
	
	
	// if the tile has no bombs around it we star clearing
	if(numAdjacent == 0){

		
		// set it to grey to mark it as 0

		if(!button->property("isFlagged").toInt()){
			button->setStyleSheet(QString("QPushButton {  background-color: #9a9a9a;    border: %1px solid #333333;    color: #0000cc;   }").arg(BUTTON_BORDER_SIZE));
		}
	
	
		for (int num : adjacentTiles){
			
			int row, column;
			
			// calculate the row and column of the button based on its flattened position
			column = num % COLUMNS;
			row = (num - column)/COLUMNS;

			// get the pointer to the button
			QLayoutItem* item = buttons->itemAtPosition(row, column);
			QPushButton* button = qobject_cast<QPushButton*>(item->widget());
			
			// if the button isn't already pressed recursivley search it 
			if(!button->property("isPressed").toBool()){
				clear_empty_tiles(button);
			}
			
		}
		
	}
	else if(!button->property("isFlagged").toInt()){
		// setting the colours for the numbers basically guessed these colours

		switch(numAdjacent){

			case 1:
				button->setStyleSheet(QString("QPushButton {    font-weight: bold;    background-color: #9a9a9a;    border: %1px solid #333333;    color: #0000cc;   }").arg(BUTTON_BORDER_SIZE));
				break;
			case 2:
				button->setStyleSheet(QString("QPushButton {    font-weight: bold;    background-color: #9a9a9a;    border: %1px solid #333333;    color: #008000;   }").arg(BUTTON_BORDER_SIZE));
				break;
			case 3:
				button->setStyleSheet(QString("QPushButton {    font-weight: bold;    background-color: #9a9a9a;    border: %1px solid #333333;    color: #cc0000;   }").arg(BUTTON_BORDER_SIZE));
				break;
			case 4:
				button->setStyleSheet(QString("QPushButton {    font-weight: bold;    background-color: #9a9a9a;    border: %1px solid #333333;    color: #9900bb;   }").arg(BUTTON_BORDER_SIZE));
				break;
			case 5:
				button->setStyleSheet(QString("QPushButton {    font-weight: bold;    background-color: #9a9a9a;    border: %1px solid #333333;    color: #000080;   }").arg(BUTTON_BORDER_SIZE));
				break;
			case 6:
				button->setStyleSheet(QString("QPushButton {    font-weight: bold;    background-color: #9a9a9a;    border: %1px solid #333333;    color: #008080;   }").arg(BUTTON_BORDER_SIZE));
				break;
			case 7:
				button->setStyleSheet(QString("QPushButton {    font-weight: bold;    background-color: #9a9a9a;    border: %1px solid #333333;    color: #ff8c00;   }").arg(BUTTON_BORDER_SIZE));
				break;
			case 8:
				button->setStyleSheet(QString("QPushButton {    font-weight: bold;    background-color: #9a9a9a;    border: %1px solid #333333;    color: #808080;   }").arg(BUTTON_BORDER_SIZE));
				break;
		
		}
		
		// now set the text
		string numBombs = to_string(numAdjacent);
		button->setText(QString::fromStdString(numBombs));

	}
	
	return;
	
}


void MainWindow :: show_bombs(){

	for(int i = 0; i < ROWS * COLUMNS; i++){

		int column = i % COLUMNS;
		int row = (i - column)/COLUMNS;

		// get the pointer to the button
		QLayoutItem* item = buttons->itemAtPosition(row, column);
		QPushButton* button = qobject_cast<QPushButton*>(item->widget());

		if(button->property("isPressed").toInt()){
			continue;
		}

		if(button->property("isFlagged").toInt()){
			if(button->property("isBomb").toInt()){
				// it was flagged correcty do nothing
			}
			else{
				button->setIcon(QIcon(":images/no_bomb.png"));
				QSize buttonSize = button->size();
				QSize iconSize(buttonSize.width() - 2 * BUTTON_BORDER_SIZE, buttonSize.height() - 2 * BUTTON_BORDER_SIZE);
				button->setIconSize(iconSize);
			}
		}
		else{
			if(button->property("isBomb").toInt()){
				button->setIcon(QIcon(":images/bomb_unexploded.png"));
				QSize buttonSize = button->size();
				QSize iconSize(buttonSize.width() - 2 * BUTTON_BORDER_SIZE, buttonSize.height() - 2 * BUTTON_BORDER_SIZE);
				button->setIconSize(iconSize);
			}
		}
	}


}

// function to handle right clicks
void MainWindow :: handleRightButton(){

	if(gameOver){
		return;
	}
	
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
			button->setIcon(QIcon(":images/mine_flag.png"));
			QSize buttonSize = button->size();
			QSize iconSize(buttonSize.width() - 2 * BUTTON_BORDER_SIZE, buttonSize.height() - 2 * BUTTON_BORDER_SIZE);
			button->setIconSize(iconSize);
			button->setProperty("isFlagged", 1);
		}
	}
	
}

// function to handle left clicks
void MainWindow :: handleLeftButton(){

	// get the button/tile they pushed
	QPushButton* button = qobject_cast<QPushButton*>(sender());

	if(button->property("isFlagged").toInt() || gameOver){
		return;
	}

	// catch null pointers
	if (button) {
		
		// if this button has been pressed before do nothing
		if(button->property("isPressed").toInt()){
			return;
		}
		
	}
	else{
		throw("How did we get here?");
	}
	
	button->setIcon(QIcon());

	
	// see if the button we pressed in a bomb
	if (button->property("isBomb").toInt()){
		
		// show the exploded bomb etc
		button->setIcon(QIcon(":images/bomb_explode.png"));
		QSize buttonSize = button->size();
		QSize iconSize(buttonSize.width() - 2 * BUTTON_BORDER_SIZE, buttonSize.height() - 2 * BUTTON_BORDER_SIZE);
		button->setIconSize(iconSize);
		button->setProperty("isPressed", 1);

		// set game over
		gameOver = 1;

		// now reveal all unexploded bombs
		show_bombs();
		
		NewGame* newGameMenu = new NewGame(nullptr, this, ROWS, COLUMNS, NUM_BOMBS);
		newGameMenu->show();
				
	}
	else{ // if it isn't a bomb we start clearing with the recursive helper function		

		clear_empty_tiles(button);

	}

}

