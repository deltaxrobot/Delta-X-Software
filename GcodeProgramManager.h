#pragma once

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
#include <qfile.h>
#include <qtextstream.h>
#include <qplaintextedit.h>
#include <qurl.h>
#include <qvector.h>
#include <qdir.h>
#include <UnityTool.h>
#include <GcodeProgram.h>
#include <qtimer.h>
#include <ConnectionManager.h>
#include <DeltaVisualizer.h>
#include <codeeditor.h>
#include <qscrollarea.h>
#include <qscrollbar.h>
#include "RobotWindow.h"
#include <QtMath>
#include "ScurveInterpolator.h"
#include <QSettings>

class RobotWindow;

class GcodeProgramManager : public QObject
{
	Q_OBJECT

public:
	GcodeProgramManager(RobotWindow *parent);
	~GcodeProgramManager();
	GcodeProgramManager(RobotWindow *parent, QScrollArea* scrolArea, QWidget* container, CodeEditor* gcodeArea, QPushButton* executeButton, ConnectionManager* deltaPort = NULL, DeltaVisualizer* deltaVisualize = NULL);
	void AddGcodeLine(QString line);
	void AddG01(float  x, float y, float z);
	void AddG28();
	void AddM204(float accel);
    GcodeProgram* AddNewProgram();
	void LoadPrograms();
    void LoadPrograms(QDir dir);

    void SaveSettings(QSettings* setting);
    void LoadSettings(QSettings* setting);

    void SelectProgram(QString name);

    QStringList GetProgramNames();

	QWidget* wgProgramContainer;
	QScrollArea* saProgramFilesScrollArea;
	CodeEditor* pteGcodeArea;
	QPushButton* pbExecuteGcodes;
    QLineEdit* leGcodeProgramPath = NULL;

	GcodeProgram* selectingProgram = NULL;
	int ProgramCounter = 0;
	QVector<GcodeProgram*>* ProgramList = NULL;

    /*!
     Parameter: - Conveyor: speed, direction
                - Robot: speed, acceleration, start speed, end speed, position
     */
    bool IsConveyorSync = false;
    float syncStartArea = -100;
    float syncEndArea = 100;

	bool IsFromOtherGcodeProgram = false;
	GcodeProgramManager* OutsideGcodeProgramManager = NULL;
	GcodeProgramManager* InsideGcodeProgramManager = NULL;

    QStringList DeltaGcodeFiles;

    Scurve_Interpolator DeltaXSMoving;

public slots:
	void ChangeSelectingProgram(GcodeProgram* ptr);
	void SaveGcodeIntoFile();
    void SaveGcodeIntoFile(GcodeProgram* program);
	void DeleteProgram(GcodeProgram* ptr);
	void EraserAllProgramItems();
	void SortProgramFiles();
    void RefreshGcodeProgramList();

    void SelectGcodeProgramPath();

private:
	ConnectionManager* deltaConnection;
    DeltaVisualizer* deltaParameter;

    int sortMethod = 0;

	RobotWindow* mParent;

    QString getTrueProgramPath();
};

