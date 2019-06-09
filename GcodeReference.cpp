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
	QString s = ui.textEdit->toHtml();
	QString ss = s;
	QTextCursor textCursor(ui.textEdit->document());

}

GcodeReference::~GcodeReference()
{

}
