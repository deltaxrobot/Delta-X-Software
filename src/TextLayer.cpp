#include "TextLayer.h"

TextLayer::TextLayer(QWidget *parent)
	: QLineEdit(parent)
{

}

TextLayer::~TextLayer()
{

}

void TextLayer::mousePressEvent(QMouseEvent * event)
{
	emit click();
}
