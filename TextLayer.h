#pragma once

#include <QLineEdit>

#define DEFAULT_COLOR				0
#define SELECTED_COLOR				1

class TextLayer : public QLineEdit
{
	Q_OBJECT

public:
	TextLayer(QWidget *parent);
	~TextLayer();

signals:
	void click();

protected:
	void mousePressEvent(QMouseEvent *event);
};
