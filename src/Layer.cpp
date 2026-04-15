#include "Layer.h"

Layer::Layer(QWidget *parent)
	: QFrame(parent)
{
}

Layer::~Layer()
{
}

void Layer::mousePressEvent(QMouseEvent * event)
{
	emit click();
}
