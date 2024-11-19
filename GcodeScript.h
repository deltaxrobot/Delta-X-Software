#ifndef GCODE_SCRIPT
#define GCODE_SCRIPT

#include <QObject>
#include "UnityTool.h"
#include <QMap>
#include <QtMath>
#include <QMutex>
#include <QElapsedTimer>
#include "Parameter.h"
#include "SoftwareManager.h"
#include <QFileInfo>
#include <QVector3D>
#include <QMatrix>
#include <QTransform>
#include <QVariant>

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

    QString ProjectName = "project0";

    QString DefaultRobot = "robot0";
    QString DefaultConveyor = "conveyor0";
    QString DefaultEncoder = "encoder0";
    QString DefaultSlider = "slider0";
    QString DefaultDevice = "device0";
    QString ID = "thread0";

    void SetGcodeScript(QString gcode);
    QString GetGcodeScript();
    void SetProgramPath(QString path);
    QString GetProgramPath();
    QString GetProgramName();
    bool IsRunning();

public slots:
    void ExecuteGcode(QString gcodes, int position, QString functions = "");
    void GetResponse(QString deviceId, QString response);
    void SendMsgToDevice(QString deviceId, QString msg);
    void TransmitNextGcode();
    void ExecuteFunction(QString functionName, QStringList paras);
    void Stop();
    void ReceivedGcode(QString gcode);

signals:
    void Finished();
    void Moved(int cursorPos);
    void RobotMoved(float x, float y, float z, float w, float u, float v, float f, float a, float s, float e);
    void RobotMoved(QString gcode);

    void DeleteAllObjects();
    void DeleteAllObjects(QString listName);
    void DeleteObject(int id);
    void PauseCamera();
    void CaptureCamera();
    void ResumeCamera();

    void UpdateTrackingRequest(int id);
    void GetObjectsRequest(int trackingID, QString inAreaListName, float min, float max, bool isXDirection);
    void CaptureAndDetectRequest();

    void SendGcodeToDevice(QString deviceName, QString gcode);
    void SendToDevice(QString deviceName, QString gcode);

    void CatchVariable(QString key, QString value);
    void CatchVariable2(QString key, QVariant value);

    void ChangeExternalVariable(QString cmd);
    void AddObject(QString listName, QList<QStringList> list);
private:

    bool isRunning = false;
    QString gcodeScript = "";
    QString programPath = "";
    QString programName = "";

    QString transmitDeviceId = DefaultRobot;
    QString transmitMsg = "";

    QStringList deviceNames = {"robot", "device", "conveyor", "slider", "encoder"};

    QList<QString> gcodeList;
    QString functionScripts = "";

    QVector<int> gcodeNumberList;
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

    void prepareCurrentLine();
    bool shouldSkipLine();
    void collapseGcodeLine();
    int findClosingBracket(int openIndex);

    void processGOTOStatement(const QList<QString>& valuePairs);

    float GetResultOfMathFunction(QString expression);
    bool isGlobalVariable(QString name);
    bool isConveyorGcode(QString gcode);
    bool isSlidingGcode(QString gcode);
    bool isEncoderGcode(QString gcode);
    bool isMovingGcode(QString gcode);

    bool findExeGcodeAndTransmit();

    void processVARIABLE();
    QString processFUNCTION(QString funcName, QStringList paras);

    bool handleGOTO(QList<QString> valuePairs, int i);
    bool handleIF(QList<QString> valuePairs, int i);
    bool handleVARIABLE(QList<QString> valuePairs, int i);
    bool handleDEFINE_SUBPROGRAM(QList<QString> valuePairs, int i);
    bool handleGCODE(QString transmitGcode);
    void handleSENT_TO_DEVICE(QList<QString> valuePairs, int i);

    QString calculateExpressions(QString expression);
    QString calculateExpressions2(QString expression);
    QString getLeftWord(QString s, int pos);
    QString getRightWord(QString s, int pos);
    QString deleteSpaces(QString s);
    QString formatSpaces(QString s);
    bool isNotNegative(QString s);
    QString getValueAsString(QString var);
    QVariant getValueAsQVariant(QString key);
    void updateVariables(QString str);
    void saveVariable(QString name, QString value);
    void saveVariable(QString name, QVariant value);
    void processResponse(QString response);
    bool checkExclution(QString response);

};

#endif
