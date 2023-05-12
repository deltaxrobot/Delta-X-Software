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
#include "SoftwareManager.h"
#include <QFileInfo>
#include "VarManager.h"

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

    QString ProjectName = "project0";
    Scurve_Interpolator DeltaXSMoving;

    QString DefaultRobot = "robot0";
    QString DefaultConveyor = "conveyor0";
    QString DefaultEncoder = "encoder0";
    QString DefaultSlider = "slider0";
    QString DefaultDevice = "device0";
    QString ID = "thread";

    void SetGcodeScript(QString gcode);
    QString GetGcodeScript();
    void SetProgramPath(QString path);
    QString GetProgramPath();
    QString GetProgramName();
    bool IsRunning();

public slots:
    void ExecuteGcode(QString gcodes, int position);
    void GetResponse(QString deviceId, QString response);
    void SendMsgToDevice(QString deviceId, QString msg);
    void TransmitNextGcode();
    void Stop();

signals:
    void Finished();
    void Moved(int cursorPos);
    void RobotMoved(float x, float y, float z, float w, float u, float v, float f, float a, float s, float e);
    void RobotMoved(QString gcode);

    void DeleteAllObjects();
    void DeleteObject(int id);
    void PauseCamera();
    void CaptureCamera();
    void ResumeCamera();

    void UpdateTrackingRequest(int id);
    void CaptureAndDetectRequest();

    void SendGcodeToDevice(QString deviceName, QString gcode);
    void SendToDevice(QString deviceName, QString gcode);

private:
    bool isRunning = false;
    QString gcodeScript = "";
    QString programPath = "";
    QString programName = "";

    QString transmitDeviceId = DefaultRobot;
    QString transmitMsg = "";

    QList<QString> gcodeList;
    int gcodeOrder = 0;
    int currentGcodeEditorCursor = 0;
    int returnSubProPointer[20];
    int returnPointerOrder = -1;
    QString currentLine;

    QString response = "";

    bool IsConveyorSync = false;
    float syncStartArea = -100;
    float syncEndArea = 100;

    QMap<QString, QString>* vars;

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
    QString calculateExpressions2(QString expression);
    QString getLeftWord(QString s, int pos);
    QString getRightWord(QString s, int pos);
    QString deleteSpaces(QString s);
    QString formatSpaces(QString s);
    bool isNotNegative(QString s);
    QString getValueOfVariable(QString var);
    void updateVariables(QString str);
    void saveVariable(QString name, QString value);
    void processResponse(QString response);
    bool checkExclution(QString response);

    QString convertGcodeToSyncConveyor(QString gcode);
};

#endif
