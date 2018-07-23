#pragma once

#include <QObject>
#include <qwidget.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qscrollarea.h>
#include <qobject.h>
#include <qlistwidget.h>
#include <vector>
#include <qlayout.h>

#define DEFAULT_COLOR	0
#define SELECTED_COLOR  1

class GcodeProgram : public QObject
{
	Q_OBJECT

public:
	GcodeProgram();
	GcodeProgram(QWidget *parent);
	void InitWidget();
	void InitEvents();
	void SetPosition(int x, int y);
	void SetName(QString name);
	void SetLength(int length);
	void Destroy();
	void SetColor(int color);
	
	QString GcodeData;

public slots:
	void SelectNewProgram();

signals:
	void Selected(GcodeProgram* ptr);

private:
	QWidget* container;
	QLineEdit* leProgramName;
	QFrame* frPanel;
	QLabel* lbGcodeNumber;
	QPushButton* pbDelete;	
};
