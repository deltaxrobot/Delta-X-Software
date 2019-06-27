#pragma once

#include <QFrame>

#define DEFAULT_COLOR				0
#define SELECTED_COLOR				1

class Layer : public QFrame
{
	Q_OBJECT

public:
	Layer(QWidget *parent);
	~Layer();

signals:
	void click();

protected:
	void mousePressEvent(QMouseEvent *event);
};
