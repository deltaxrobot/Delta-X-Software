#pragma once

#include <QLabel>

class DrawingWidget : public QLabel
{
	Q_OBJECT

public:
	DrawingWidget(QWidget *parent);
	~DrawingWidget();

	void InitGrid();
};
