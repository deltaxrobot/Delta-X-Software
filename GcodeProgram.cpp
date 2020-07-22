#include "GcodeProgram.h"

GcodeProgram::GcodeProgram()
{
	
}

GcodeProgram::GcodeProgram(QWidget * parent) : GcodeProgram()
{
	container = parent;

	InitWidget();
	InitEvents();

	frPanel->setParent(container);

	frPanel->setVisible(true);
}

GcodeProgram::~GcodeProgram()
{
	Destroy();
}

void GcodeProgram::InitWidget()
{
	frPanel = new Layer(container);
	frPanel->setGeometry(QRect(10, 10, 221, 71));
	frPanel->setStyleSheet(QStringLiteral("background-color:rgb(209, 209, 209)"));
	frPanel->setFrameShape(QFrame::StyledPanel);
	frPanel->setFrameShadow(QFrame::Raised);

	leProgramName = new TextLayer(frPanel);
	leProgramName->setGeometry(QRect(10, 10, 160, 30));

	QFont font;
	font.setPointSize(12);

	leProgramName->setFont(font);
	leProgramName->setCursor(QCursor(Qt::SizeHorCursor));
	leProgramName->setStyleSheet(QStringLiteral(""));

	pbDelete = new QPushButton(frPanel);
	QIcon icon1;
	icon1.addFile(QStringLiteral("icon/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
	pbDelete->setIcon(icon1);
	pbDelete->setIconSize(QSize(30, 30));
	pbDelete->setGeometry(QRect(180, 10, 30, 31));
	pbDelete->setAutoDefault(false);
	pbDelete->setFlat(true);
	pbDelete->setDefault(true);

	lbGcodeNumber = new QLabel(frPanel);
	lbGcodeNumber->setGeometry(QRect(10, 50, 100, 15));
	lbGcodeNumber->setText("0 Gcode Lines");
}

void GcodeProgram::InitEvents()
{
	connect(leProgramName, SIGNAL(click()), this, SLOT(SelectNewProgram()));
	connect(frPanel, SIGNAL(click()), this, SLOT(SelectNewProgram()));
	connect(pbDelete, SIGNAL(clicked(bool)), this, SLOT(DeleteProgram()));
}

void GcodeProgram::SetPosition(int x, int y)
{
	frPanel->move(x, y);
}

void GcodeProgram::SetName(QString name)
{
	leProgramName->setText(name);
}

QString GcodeProgram::GetName()
{
	return leProgramName->text();
}

void GcodeProgram::SetLength(int length)
{
	lbGcodeNumber->setText(QString::number(length) + " Gcode Lines");
}

void GcodeProgram::CoutingGcodeLines()
{
	QList<QString> lines = GcodeData.split('\n');
	long counter = 0;

	for (long i = 0; i < lines.size(); i++)
	{
		if (lines[i] != "")
		{
			counter++;
		}
	}

	SetLength(counter);
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
	{
		frPanel->setStyleSheet(QStringLiteral("background-color:rgb(209, 209, 209)"));
	}		
	else if (color == SELECTED_COLOR)
	{
		frPanel->setStyleSheet(QStringLiteral("background-color:rgb(105, 199, 217)"));
	}
}

QPoint GcodeProgram::GetPosition()
{
	return frPanel->pos();
}

void GcodeProgram::DeleteProgram()
{
	emit Deleted(this);
}

void GcodeProgram::SelectNewProgram()
{
	SetColor(SELECTED_COLOR);
	emit Selected(this);
}
