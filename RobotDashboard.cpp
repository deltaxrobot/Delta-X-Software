#include "RobotDashboard.h"

RobotDashboard::RobotDashboard(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QMainWindow* qmw = new QMainWindow();
	qmw->setParent(ui.wgContainer);
	mw.setupUi(qmw);
}

RobotDashboard::~RobotDashboard()
{
}
