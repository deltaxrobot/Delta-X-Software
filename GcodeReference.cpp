#include "GcodeReference.h"

GcodeReference::GcodeReference(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SelectGcodeItem(QListWidgetItem*)));	
}

void GcodeReference::SelectGcodeItem(QListWidgetItem *item)
{
	ui.textEdit->scrollToAnchor(item->text());
}

GcodeReference::~GcodeReference()
{

}
