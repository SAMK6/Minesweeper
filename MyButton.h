/* 
author Sam Feldman

date Feb 6, 2024

*/

#include <QtWidgets>
#include <QPushButton>
#include <QMouseEvent>

// this custom button class extends the QPushButton to detect left and right clicks
class MyButton : public QPushButton{
	Q_OBJECT
	
public:
	explicit MyButton(QWidget *parent = nullptr);

signals:
	void leftClicked();
	void rightClicked();

protected:

	void mousePressEvent(QMouseEvent *event) override;
	
};