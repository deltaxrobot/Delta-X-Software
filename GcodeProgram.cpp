#include "GcodeProgram.h"

GcodeProgram::GcodeProgram()
{
	InitWidget();
	InitEvents();
}

GcodeProgram::GcodeProgram(QWidget * parent) : GcodeProgram()
{
	container = parent;

	frPanel->setParent(container);

	frPanel->setVisible(true);
}

void GcodeProgram::InitWidget()
{
	frPanel = new QFrame();
	frPanel->setGeometry(QRect(10, 10, 250, 80));
	frPanel->setStyleSheet(QStringLiteral("background-color:rgb(209, 209, 209)"));
	frPanel->setFrameShape(QFrame::StyledPanel);
	frPanel->setFrameShadow(QFrame::Raised);

	leProgramName = new QLineEdit(frPanel);
	leProgramName->setGeometry(QRect(10, 10, 170, 40));

	QFont font;
	font.setPointSize(12);

	leProgramName->setFont(font);
	leProgramName->setCursor(QCursor(Qt::SizeHorCursor));
	leProgramName->setStyleSheet(QStringLiteral(""));

	pbDelete = new QPushButton(frPanel);
	pbDelete->setGeometry(QRect(190, 10, 50, 40));
	pbDelete->setAutoDefault(false);
	pbDelete->setFlat(true);
	pbDelete->setDefault(true);
	pbDelete->setText("Delete");

	lbGcodeNumber = new QLabel(frPanel);
	lbGcodeNumber->setGeometry(QRect(10, 60, 100, 15));
	lbGcodeNumber->setText("0 Gcode Lines");
}

void GcodeProgram::InitEvents()
{
	connect(leProgramName, SIGNAL(selectionChanged()), this, SLOT(SelectNewProgram()));
}

void GcodeProgram::SetPosition(int x, int y)
{
	frPanel->move(x, y);
}

void GcodeProgram::SetName(QString name)
{
	leProgramName->setText(name);
}

void GcodeProgram::SetLength(int length)
{
	lbGcodeNumber->setText(QString::number(length) + " Gcode Lines");
}

void GcodeProgram::Destroy()
{
	delete leProgramName;
	delete lbGcodeNumber;
	delete pbDelete;
	delete frPanel;
}

void GcodeProgram::SetColor(int color)
{
	if (color == DEFAULT_COLOR)
		frPanel->setStyleSheet(QStringLiteral("background-color:rgb(209, 209, 209)"));
	else if (color == SELECTED_COLOR)
		frPanel->setStyleSheet(QStringLiteral("background-color:rgb(105, 199, 217)"));
}

void GcodeProgram::SelectNewProgram()
{
	SetColor(SELECTED_COLOR);
	emit Selected(this);
}
