#ifndef GCODE_SCRIPT
#define GCODE_SCRIPT

#include <QObject>
#include "UnityTool.h"
#include <QMap>
#include "ScurveInterpolator.h"
#include <QtMath>
#include <QMutex>
#include <QElapsedTimer>
#include "Parameter.h"

class GcodeScript : public QObject
{
    Q_OBJECT
public:
    GcodeScript();
    ~GcodeScript();

    enum
    {
        BEGIN = 0,
        CURSOR_POSITION,
    };

    QMap<QString, QString> *GcodeVariables = NULL;
    Scurve_Interpolator DeltaXSMoving;

public slots:
    void ExecuteGcode(QString gcodes, int position, bool isFromGcodeEditor);
    void TransmitNextGcode();
    void Stop();

signals:
    void Finished();
    void Moved(int cursorPos);
    void RobotMoved(float x, float y, float z, float w, float u, float v, float f, float a, float s, float e);
    void RobotMoved(QString gcode);

    void SaveVariable(QString key, QString value);

    void DeleteAllObjects();
    void DeleteObject1();
    void PauseCamera();
    void CaptureCamera();
    void ResumeCamera();

    void SendGcodeToDevice(QString deviceName, QString gcode);
    void SendToDevice(QString deviceName, QString gcode);

private:
    bool isFromGcodeEditor = false;
    bool isFileProgramRunning = false;

    QList<QString> gcodeList;
    int gcodeOrder = 0;
    int currentGcodeEditorCursor = 0;
    int returnSubProPointer[20];
    int returnPointerOrder = -1;
    QString currentLine;

    bool IsConveyorSync = false;
    float syncStartArea = -100;
    float syncEndArea = 100;

    QMutex mMutex;

    QElapsedTimer elapsedTimer;

    float GetResultOfMathFunction(QString expression);
    bool isGlobalVariable(QString name);
    bool isConveyorGcode(QString gcode);
    bool isSlidingGcode(QString gcode);
    bool isEncoderGcode(QString gcode);
    bool isMovingGcode(QString gcode);
    bool findExeGcodeAndTransmit();
    QString calculateExpressions(QString expression);
    QString getLeftWord(QString s, int pos);
    QString getRightWord(QString s, int pos);
    QString deleteSpaces(QString s);
    bool isNotNegative(QString s);
    QString getValueOfVariable(QString var);
    void updateVariables(QString str);

    QString convertGcodeToSyncConveyor(QString gcode);
};

#endif