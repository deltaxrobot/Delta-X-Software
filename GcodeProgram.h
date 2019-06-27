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
#include "Layer.h"
#include "TextLayer.h"

#define DEFAULT_COLOR	0
#define SELECTED_COLOR  1

class GcodeProgram : public QObject
{
	Q_OBJECT

public:
	GcodeProgram();
	GcodeProgram(QWidget *parent);
	~GcodeProgram();
	void InitWidget();
	void InitEvents();
	void SetPosition(int x, int y);
	void SetName(QString name);
	QString GetName();
	void SetLength(int length);
	void CoutingGcodeLines();
	void Destroy();
	void SetColor(int color);
	
	int ID;
	QString GcodeData;

public slots:
	void SelectNewProgram();
	void DeleteProgram();

signals:
	void Selected(GcodeProgram* ptr);
	void Deleted(GcodeProgram* ptr);

private:
	QWidget* container;
	TextLayer* leProgramName;
	Layer* frPanel;
	QLabel* lbGcodeNumber;
	QPushButton* pbDelete;	
};
