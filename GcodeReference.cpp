#include "GcodeReference.h"

GcodeReference::GcodeReference(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SelectGcodeItem(QListWidgetItem*)));	

	QString text = ui.textEdit->toPlainText();
	//connect(ui.textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(SelectLineTextEdit()));
}

void GcodeReference::SelectGcodeItem(QListWidgetItem *item)
{
	QString itemText = item->text();
	QString name = "other";

	if (itemText.indexOf(".") > -1)
	{
		name = itemText.mid(0, itemText.indexOf("."));
	}

	if (itemText.indexOf(" -") > -1)
	{
		name = itemText.mid(0, itemText.indexOf(" -"));
		name = name.replace(", ", "_");
	}

	ui.textEdit->scrollToAnchor(name);
	ui.teMacro->scrollToAnchor(name);
	QString s = ui.textEdit->toHtml();
	QString ss = s;
	QTextCursor textCursor(ui.textEdit->document());
	
	QTextCharFormat fmt = ui.textEdit->currentCharFormat();
	fmt.setUnderlineColor(Qt::red);
	fmt.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);

	QTextDocument* textDoc = ui.textEdit->document();

	QTextCursor cursor = QTextCursor(ui.textEdit->document());

	cursor.setPosition(10);
	cursor.select(QTextCursor::LineUnderCursor);
	cursor.setCharFormat(fmt);
}

GcodeReference::~GcodeReference()
{

}

void GcodeReference::SelectLineTextEdit()
{
	QTextCharFormat fmt = ui.textEdit->currentCharFormat();
	fmt.setUnderlineColor(Qt::red);
	fmt.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);

	QTextCursor cursor;
	QString text;

	cursor = ui.textEdit->textCursor();
	cursor.movePosition(QTextCursor::StartOfBlock);
	cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
	text = cursor.selectedText();

	cursor.setCharFormat(fmt);
}
