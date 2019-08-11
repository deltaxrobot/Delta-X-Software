#pragma once

#include <QWidget>
#include "ui_RobotDashboard.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

class RobotDashboard : public QWidget
{
	Q_OBJECT

public:
	RobotDashboard(QWidget *parent = Q_NULLPTR);
	~RobotDashboard();

private:
	Ui::MainWindow mw;
	Ui::RobotDashboard ui;
};
