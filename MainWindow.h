/* 
author Sam Feldman

date Feb 6, 2024

*/

#include <QMainWindow>
#include <QPushButton>
#include <QMainWindow>
#include <QGridLayout>
#include <set>

using namespace std;

// custom window to hold the game
class MainWindow : public QMainWindow {
	
	Q_OBJECT
	
public:

	explicit MainWindow(QWidget *parent = nullptr);
	
private slots:
	void handleRightButton();
	void handleLeftButton();
	
private:

	void clear_empty_tiles(QPushButton*);
	
	QGridLayout* buttons;

	const int BUTTON_SIZE = 50;
	const int BUTTON_BORDER_SIZE = 2;

	const int NUM_BOMBS = 99;

	const int ROWS = 16;
	const int COLUMNS = 30;

	set<int> bombPositions;
	
};

