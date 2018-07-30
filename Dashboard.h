#pragma once

#include <qwidget.h>
#include <qlineedit.h>
#include <ConnectionManager.h>

class Dashboard : public QWidget
{
	Q_OBJECT
public:
	Dashboard(ConnectionManager* connectManager, QLineEdit* lex, QLineEdit* ley, QLineEdit* lez);
	~Dashboard();

	float X;
	float Y;
	float Z;

public slots:
	void UpdatePosition();
	void UpdatePosition(QString gcode);
	void Home();
	void UpdateZ();
	void UpdateY();
	void UpdateX();
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

private:
	ConnectionManager* deltaPort;
	QLineEdit* leX;
	QLineEdit* leY;
	QLineEdit* leZ;
};

