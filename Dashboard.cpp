#include "Dashboard.h"

Dashboard::Dashboard(ConnectionManager* connectManager, QLineEdit* lex, QLineEdit* ley, QLineEdit* lez)
{
	deltaPort = connectManager;
	leX = lex;
	leY = ley;
	leZ = lez;
}

void Dashboard::UpdatePosition()
{

}

Dashboard::~Dashboard()
{
}

void Dashboard::UpdatePosition(QString gcode)
{
	if (gcode.count('X') > 0)
	{
		int xPos = gcode.lastIndexOf('X');
		int spacePos = gcode.indexOf(' ', xPos);
		QString sX = gcode.mid(xPos + 1, spacePos - xPos);
		SetX(sX.toFloat());
	}

	if (gcode.count('Y') > 0)
	{
		int yPos = gcode.lastIndexOf('Y');
		int spacePos = gcode.indexOf(' ', yPos);
		QString sY = gcode.mid(yPos + 1, spacePos - yPos);
		SetY(sY.toFloat());
	}

	if (gcode.count('Z') > 0)
	{
		int zPos = gcode.lastIndexOf('Z');
		int spacePos = gcode.indexOf(' ', zPos);
		QString sZ = gcode.mid(zPos + 1, spacePos - zPos);
		SetZ(sZ.toFloat());
	}
}

void Dashboard::Home()
{
	deltaPort->ExecuteGcode("G28");

	leX->setText("0");
	leY->setText("0");
	leZ->setText("-230");

	X = 0;
	Y = 0;
	Z = -230;
}

void Dashboard::UpdateZ()
{
	deltaPort->ExecuteGcode(QString("G01 Z") + leZ->text());
	Z = leZ->text().toFloat();
}

void Dashboard::UpdateY()
{
	deltaPort->ExecuteGcode(QString("G01 Y") + leY->text());
	Y = leY->text().toFloat();
}

void Dashboard::UpdateX()
{
	deltaPort->ExecuteGcode(QString("G01 X") + leX->text());
	X = leX->text().toFloat();
}

void Dashboard::SetX(float x)
{
	X = x;
	leX->setText(QString::number(X));
}

void Dashboard::SetY(float y)
{
	Y = y;
	leY->setText(QString::number(Y));
}

void Dashboard::SetZ(float z)
{
	Z = z;
	leZ->setText(QString::number(Z));
}
